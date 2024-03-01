#include <iostream>
using namespace std;

// Strategy interface
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() {}
    virtual void processPayment(double amount) = 0;
};

// Concrete strategies
class CreditCardPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

class VenmoPayment : public PaymentStrategy {
public:
    void processPayment(double amount) override {
        cout << "Processing Venmo payment of $" << amount << endl;
    }
};

class TestPayment {
private:
    PaymentStrategy* paymentStrategy;

public:
    TestPayment(PaymentStrategy* strategy) : paymentStrategy(strategy) {}

    void setPaymentStrategy(PaymentStrategy* strategy) {
        paymentStrategy = strategy;
    }

    void processPayment(double amount) {
        if (paymentStrategy) {
            paymentStrategy->processPayment(amount);
        } else {
            cout << "No payment strategy set." << endl;
        }
    }
};

int main() {
    CreditCardPayment creditCardPayment;
    PayPalPayment payPalPayment;
    VenmoPayment venmoPayment;

    TestPayment testPayment(&creditCardPayment);
    testPayment.processPayment(100.0);

    testPayment.setPaymentStrategy(&payPalPayment);
    testPayment.processPayment(50.0);

    testPayment.setPaymentStrategy(&venmoPayment);
    testPayment.processPayment(30.0);

    return 0;
}
