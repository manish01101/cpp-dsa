// Cab Locator Project in C++

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>

const double EARTH_RADIUS_KM = 6371.0;

struct Cab {
    std::string id;
    double latitude;
    double longitude;
    double distanceFromUser;
};

double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);

    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = pow(sin(dLat / 2), 2) +
               cos(lat1) * cos(lat2) * pow(sin(dLon / 2), 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

std::vector<Cab> loadCabsFromCSV(const std::string& filename) {
    std::vector<Cab> cabs;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id;
        double lat, lon;
        char comma;

        if (std::getline(ss, id, ',') && ss >> lat >> comma >> lon) {
            cabs.push_back({id, lat, lon, 0.0});
        }
    }

    return cabs;
}

void displayCabMapLink(double userLat, double userLon, const Cab& cab) {
    std::cout << "\nMap: https://www.google.com/maps/dir/"
              << userLat << "," << userLon << "/"
              << cab.latitude << "," << cab.longitude << "\n";
}

int main() {
    double userLat, userLon;
    std::cout << "Enter your current location (latitude and longitude): ";
    std::cin >> userLat >> userLon;

    std::vector<Cab> cabs = loadCabsFromCSV("cabs.csv");

    if (cabs.empty()) {
        std::cout << "No cabs found. Check the CSV file.\n";
        return 1;
    }

    for (auto& cab : cabs) {
        cab.distanceFromUser = haversine(userLat, userLon, cab.latitude, cab.longitude);
    }

    std::sort(cabs.begin(), cabs.end(), [](Cab a, Cab b) {
        return a.distanceFromUser < b.distanceFromUser;
    });

    const Cab& nearestCab = cabs[0];
    std::cout << "\nNearest Cab: " << nearestCab.id
              << "\nLocation: (" << nearestCab.latitude << ", " << nearestCab.longitude << ")"
              << "\nDistance: " << std::fixed << std::setprecision(2)
              << nearestCab.distanceFromUser << " km\n";

    displayCabMapLink(userLat, userLon, nearestCab);

    std::cout << "\nWould you like to book this cab and pay online? (yes/no): ";
    std::string choice;
    std::cin >> choice;

    if (choice == "yes") {
        std::cout << "\nRedirecting to Payment Gateway (simulated)...\n";
        std::cout << "Payment of Rs. 150 successful. Cab booked!\n";
    } else {
        std::cout << "\nCab not booked. Thank you for using the service.\n";
    }

    return 0;
}
