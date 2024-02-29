#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class NewsData;

class NewsObserver {
public:
    virtual void update(const NewsData& newsData) = 0;
};

class NewsData {
private:
    string latestNews;
    vector<NewsObserver*> observers;

public:
    void addObserver(NewsObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(NewsObserver* observer) {
        observers.erase(remove_if(observers.begin(), observers.end(), [observer](NewsObserver* obs) {
            return obs == observer;
        }), observers.end());
    }


    void notifyObservers() {
        for (NewsObserver* observer : observers) {
            observer->update(*this);
        }
    }

    void setLatestNews(const string& news) {
        latestNews = news;
        notifyObservers();
    }

    string getLatestArticle() const {
        return latestNews;
    }
};

// Concrete observer classes

class EmailObserver : public NewsObserver {
public:
    void update(const NewsData& newsData) override {
        // Send an email with the latest news
        cout << "Latest news article shared through email: " << newsData.getLatestArticle() << endl;
    }
};

class SMSObserver : public NewsObserver {
public:
    void update(const NewsData& newsData) override {
        // Send an SMS with the latest news
        cout << "Latest news article shared through SMS: " << newsData.getLatestArticle() << endl;
    }
};

class NewsAppObserver : public NewsObserver {
public:
    void update(const NewsData& newsData) override {
        // Display the latest news in the news app
        cout << "Displaying news in the app: " << newsData.getLatestArticle() << endl;
    }
};



int main() {
    // Create instances of concrete observers
    EmailObserver emailObserver;
    SMSObserver smsObserver;
    NewsAppObserver newsAppObserver;
    NewsData newsData;

    newsData.addObserver(&emailObserver);
    newsData.addObserver(&smsObserver);
    newsData.addObserver(&newsAppObserver);

    // Set the latest news
    newsData.setLatestNews("Redwood City-based Electronic Arts is laying off hundreds of workers. Read More about this...");

    newsData.removeObserver(&smsObserver);

    newsData.setLatestNews("Australia's Great Barrier Reef suffers 'extensive' coral bleaching, as scientists fear seventh mass bleaching event. Read More about this...");

    return 0;
}
