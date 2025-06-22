#ifndef FINE_H
#define FINE_H
#include <iostream>
using namespace std;

class Fine {
    private:
        float ratePerDay;
        float fineAmount;
    
    public:
        Fine(float rate = 100) : ratePerDay(rate) {}
        ~Fine() {}
    
        void calculateFine(string dueDate, string returnDate) {
            int returnDay, returnMonth, returnYear;
            int dueDay, dueMonth, dueYear;
    
            sscanf(returnDate.c_str(), "%d/%d/%d", &returnDay, &returnMonth, &returnYear);
            sscanf(dueDate.c_str(), "%d/%d/%d", &dueDay, &dueMonth, &dueYear);
    
            // Calculate fine based on the difference in days
            int daysLate = (returnYear - dueYear) * 365 + (returnMonth - dueMonth) * 30 + (returnDay - dueDay);
    
            if (daysLate > 0) {
                fineAmount = daysLate * 100.0; // Assuming Rs. 100 per day fine
            } else {
                fineAmount = 0.0; // No fine if returned on time
            }
        }
        float getFineAmount() const {
            return fineAmount;
        }
};

    

#endif