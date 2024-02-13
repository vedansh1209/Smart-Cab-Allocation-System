#include <bits/stdc++.h>

using namespace std;

// Class to represent a location (latitude, longitude)
class Location 
{
private:
    double latitude;
    double longitude;

public:
    Location(double lat, double lon) : latitude(lat), longitude(lon) {}

    double getLatitude() const { return latitude; }

    double getLongitude() const { return longitude; }

    // Method to calculate distance between two locations using Haversine formula
    double distanceTo(const Location& other) const 
    {
        const double earthRadiusKm = 6371.0;
        double dLat = (other.latitude - latitude) * M_PI / 180.0;
        double dLon = (other.longitude - longitude) * M_PI / 180.0;
        double lat1 = latitude * M_PI / 180.0;
        double lat2 = other.latitude * M_PI / 180.0;

        double a = sin(dLat / 2.0) * sin(dLat / 2.0) +
                   sin(dLon / 2.0) * sin(dLon / 2.0) * cos(lat1) * cos(lat2);
        double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
        return earthRadiusKm * c;
    }
};

// User class for authentication
class User 
{
private:
    string username;
    string password;
public:
    // Default constructor
    User() {}

    User(string uname, string pwd) : username(uname), password(pwd) {}

    string getUsername() const { return username; }

    bool authenticate(string uname, string pwd) const
    {
        return (username == uname && password == pwd);
    }
};

// Cab class representing a single cab
class Cab 
{
private:
    string id;
    Location currentLocation;
public:
    Cab(string cid, double lat, double lon) : id(cid), currentLocation(lat, lon) {}

    string getId() const { return id; }

    Location getCurrentLocation() const { return currentLocation; }

    // Other methods for cab operations
};

// CabAllocationSystem class managing cab allocation and authentication
class CabAllocationSystem
{
private:
    unordered_map<string, User> users;
    vector<Cab> availableCabs;
public:
    // Method to add a new user
    void addUser(string username, string password) 
    {
        users.emplace(username, User(username, password));
    }

    // Method to add a new cab
    void addCab(string id, double lat, double lon) 
    {
        availableCabs.emplace_back(id, lat, lon);
    }

    // Method to authenticate a user
    bool authenticateUser(string username, string password) 
    {
        if (users.find(username) != users.end()) 
        {
            return users[username].authenticate(username, password);
        }
        return false;
    }

    // Method to suggest the best cab based on proximity to the trip start location
    Cab suggestBestCab(const Location& tripStartLocation) const 
    {
        double minDistance = numeric_limits<double>::max();
        Cab bestCab("", 0.0, 0.0);

        for (const Cab& cab : availableCabs) 
        {
            double distance = cab.getCurrentLocation().distanceTo(tripStartLocation);
            if (distance < minDistance) 
            {
                minDistance = distance;
                bestCab = cab;
            }
        }

        return bestCab;
    }

};

int main() {
    CabAllocationSystem system;

    // Adding Admin
    system.addUser("admin", "admin123");

    // Adding cabs("Car(Reg No.)", LOCATION)
    system.addCab("Swift(MH 20 B 5678)", 19.0760, 72.8777);
    system.addCab("Innova(TN 07 D 4321)", 13.0827, 80.2707);
    system.addCab("Verna(AP 03 F 7890)", 17.3850, 78.4867);
    system.addCab("Baleno(DL 05 G 2468)", 28.7041, 77.1025);
    system.addCab("XUV500(KA 01 H 1357)", 12.9716, 77.5946);
    system.addCab("Ciaz(RJ 14 J 6543)", 26.9124, 75.7873);
    system.addCab("Alto(KL 10 K 3698)", 9.9312, 76.2673);
    system.addCab("Dzire(GJ 18 L 2019)", 23.0225, 72.5714);
    system.addCab("City(WB 22 M 2845)", 22.5726, 88.3639);
    system.addCab("i20(UP 15 N 3759)", 26.8467, 80.9462);

    cout<<endl<<"|| MoveInSync Nearest Cab Locator ||"<<endl<<endl;

    //Login/SignUp Interface
    int inp;
    cout<<"1. New User ~ Sign UP"<<endl;
    cout<<"2. Existing User ~ Login"<<endl;

    cout<<endl<<"INPUT :";
    cin>>inp;

    cout<<endl;

    string username, password;

    if(inp==2)
    {
        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;
    }

    else if(inp==1)
    {
        cout << "Please enter your username: ";
        cin >> username;
        cout << "Please enter your password: ";
        cin >> password;
        system.addUser(username, password);
        cout<<endl<<"Account Created successful :) "<<endl<<endl;
    }

    else
    {
        cout<<"INVALID INPUT"<<endl;
        return 0;
    }
    // Authentication
    if (system.authenticateUser(username, password)) 
    {
        cout << "Authentication successful! Welcome, " << username << "!" << endl;

        // Input trip start location
        double startLat, startLon;
        cout <<endl<< "Enter trip start location (latitude, longitude): ";
        cin >> startLat >> startLon;
        //Later can be integrated with a API
        Location tripStartLocation(startLat, startLon);

        // Suggest the best cab for the trip
        Cab bestCab = system.suggestBestCab(tripStartLocation);

        cout <<"Nearest cab for the trip: " << bestCab.getId() << endl;

    } 
    else 
    {
        cout << "Authentication failed! Invalid username or password." << endl;
    }

    return 0;
}