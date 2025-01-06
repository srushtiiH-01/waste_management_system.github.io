#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <fstream>
#include <cmath>
#include <limits>
#include <functional>

using namespace std;

// Structure to store the data of each area
struct Area {
    int id;
    // ID of the area
    string name;
    // Name of the area
    double wasteQuantity;
     // Total quantity of waste generated (in tons)
    string wasteCategory;
    // Category of waste (e.g., Plastic, Organic, Electronic)
    double areaSize;
     // Area size in square kilometers
    string location;
     // Physical location of the area
    int population;
     // Population of the area
    time_t lastUpdated;
    // Time when the data was last updated
    string wasteManagementStrategy;
    // Waste management strategy (e.g., Recycling, Composting)
    double environmentalImpactScore;
     // Environmental impact score (0-100)
    double budgetAllocated;
     // Budget allocated for waste management


    // Default constructor to initialize all members with default values

    Area() : id(0), name(""), wasteQuantity(0.0), wasteCategory("General"), areaSize(0.0),
             location(""), population(0), lastUpdated(time(0)), wasteManagementStrategy("None"),
             environmentalImpactScore(0.0), budgetAllocated(0.0) {}

    // Parametrized constructor to initialize all members with specific values

    Area(int id, string name, double wasteQuantity, string wasteCategory, double areaSize,
         string location, int population, time_t lastUpdated, string wasteManagementStrategy,
         double environmentalImpactScore, double budgetAllocated)
         : id(id), name(name), wasteQuantity(wasteQuantity), wasteCategory(wasteCategory),
           areaSize(areaSize), location(location), population(population), lastUpdated(lastUpdated),
           wasteManagementStrategy(wasteManagementStrategy), environmentalImpactScore(environmentalImpactScore),
           budgetAllocated(budgetAllocated) {}

    // Method to display area details in tabular format

    void displayAreaInfo() const {

        // Displaying area details in a structured format for readability
        cout << left << setw(2) << id // Displaying ID with 10 characters width

             << setw(17) << name // Displaying area name with 25 characters width

             << setw(6) << wasteQuantity // Displaying waste quantity with 20 characters width
             << setw(11) << wasteCategory // Displaying waste category with 15 characters width

             << setw(3) << areaSize // Displaying area size with 15 characters width

             << setw(7) << location // Displaying location with 20 characters width

             << setw(6) << population // Displaying population with 12 characters width


             << setw(10) << wasteManagementStrategy // Displaying waste management strategy with 20 characters width

             << setw(13) << environmentalImpactScore // Displaying environmental impact score with 18 characters width

             << setw(12) << budgetAllocated // Displaying budget allocated with 15 characters width

             << setw(25) << ctime(&lastUpdated) // Print time in readable format using ctime

             << endl;
    }

    // Method to calculate waste density (Waste quantity per square km)
    double calculateWasteDensity() const {


        // Prevent division by zero by checking if area size is greater than 0
        return areaSize > 0 ? wasteQuantity / areaSize : 0;
    }

    // Method to calculate the environmental impact based on various factors

    double calculateEnvironmentalImpact() const {
        // Environmental impact score calculation based on waste quantity and environmental impact score
        return environmentalImpactScore * (wasteQuantity / 1000);
    }


    // Method to get the age of the area in days since last update

    int getDaysSinceLastUpdate() const {
        time_t now = time(0); // Get the current time
        return difftime(now, lastUpdated) / (60 * 60 * 24); // Convert seconds to days
    }
};

// Graph class to represent a weighted graph of areas
class Graph {

public:

    unordered_map<int, Area> nodes; // Hashmap to store areas by their ID

    // Method to add a new area to the system
    void addArea(int id, string name, double wasteQuantity, string wasteCategory, double areaSize,
                 string location, int population, time_t lastUpdated, string wasteManagementStrategy,
                 double environmentalImpactScore, double budgetAllocated) {
        // Create a new Area object and add it to the 'nodes' map using the area ID as the key
        nodes[id] = Area(id, name, wasteQuantity, wasteCategory, areaSize, location, population,
                         lastUpdated, wasteManagementStrategy, environmentalImpactScore, budgetAllocated);
    }


    // Method to display all areas in the system in tabular format

    void displayAreas() const {
        // Displaying column headers for the tabular format
          cout << "\nAreas in the system (sorted by waste quantity):\n";
            cout << left << setw(2) << "AID"

         << setw(17) << "ArName"

         << setw(6) << "Waste qun(t)"

         << setw(11) << "Waste Cat"

         << setw(3) << "Ar Size(sq.km)"

         << setw(7) << "Loc"

         << setw(6) << "Popu"

         << setw(10) << "Waste Manag st"

         << setw(3) << "Environ Impact"

         << setw(12) << "Budget Alloc"

         << setw(25) << "Last Updated"

         << endl;


        // Loop through all areas and display their data

        for (auto& entry : nodes) {
            entry.second.displayAreaInfo(); // Call the display method for each area
        }
    }

    // Method to sort areas by waste quantity in descending order

    void sortAreasByWaste() {
        // Convert unordered_map to vector for sorting purposes
        vector<pair<int, Area>> areaList(nodes.begin(), nodes.end());

        // Sorting the vector based on waste quantity in descending order

        sort(areaList.begin(), areaList.end(), [](const pair<int, Area>& a, const pair<int, Area>& b) {
            return a.second.wasteQuantity > b.second.wasteQuantity; // Compare waste quantities
        });

        // Clear the original map and insert the sorted areas back into the map
        nodes.clear();
        for (auto& area : areaList) {
            nodes[area.first] = area.second;
        }
    }

    // Method to filter and display areas based on waste category

    void displayAreasByCategory(const string& category) const {
        // Displaying all areas matching the given waste category

        cout << "\nAreas with waste category: " << category << "\n";
        for (auto& entry : nodes) {
            if (entry.second.wasteCategory == category) {
                entry.second.displayAreaInfo(); // Display only matching areas
            }
        }
    }

    // Method to update data for a specific area
    void updateAreaData(int id) {
        if (nodes.find(id) != nodes.end()) {
            // If the area exists, allow updating its data
            Area& area = nodes[id];

            cout << "Enter new data for area ID " << id << " (" << area.name << "):\n";

            cout << "Enter waste quantity: ";

            cin >> area.wasteQuantity;

            cout << "Enter waste category: ";

            cin.ignore(); // To ignore the newline left by previous input

            getline(cin, area.wasteCategory);

            cout << "Enter area size: ";

            cin >> area.areaSize;

            cout << "Enter location: ";

            cin.ignore();

            getline(cin, area.location);

            cout << "Enter population: ";

            cin >> area.population;

            cout << "Enter waste management strategy: ";

            cin.ignore();

            getline(cin, area.wasteManagementStrategy);

            cout << "Enter environmental impact score: ";

            cin >> area.environmentalImpactScore;

            cout << "Enter budget allocated: ";

            cin >> area.budgetAllocated;

            area.lastUpdated = time(0); // Update the timestamp for when the data was updated

            cout << "Area data updated successfully!\n";
        } else {
            cout << "Area ID " << id << " not found!\n";
        }
    }

    // Method to delete an area by its ID

    void deleteArea(int id) {

        if (nodes.find(id) != nodes.end()) {

            // If area exists, erase it from the map

            nodes.erase(id);

            cout << "Area ID " << id << " has been deleted.\n";
        } else {
            cout << "Area ID " << id << " not found!\n";
        }
    }

    // Method to save data to a file

    void saveToFile(const string& filename) const {

        ofstream outFile(filename); // Open file for writing

        if (outFile.is_open()) {

            // Loop through all areas and write their data to the file

            for (const auto& entry : nodes) {

                const Area& area = entry.second;

                outFile << area.id << ","

                        << area.name << ","


                        << area.wasteQuantity << ","


                        << area.wasteCategory << ","

                        << area.areaSize << ","

                        << area.location << ","



                        << area.wasteManagementStrategy << ","

                         << area.population << ","

                        << area.environmentalImpactScore << ","

                        << area.budgetAllocated << ","

                        << ctime(&area.lastUpdated) << "\n"; // Use ctime for readable time format
            }
            cout << "Data saved to " << filename << endl;
        } else {
            cout << "Error saving data to file.\n";
        }
    }

    // Method to load data from a file
    void loadFromFile(const string& filename) {
        ifstream inFile(filename); // Open file for reading
        if (inFile.is_open()) {
            string line;
            // Reading the file line by line
            while (getline(inFile, line)) {
                stringstream ss(line);
                string idStr, name, wasteQuantityStr, wasteCategory, areaSizeStr, location, populationStr,
                        wasteManagementStrategy, environmentalImpactStr, budgetAllocatedStr, lastUpdatedStr;

                // Parsing the CSV line into individual components
                getline(ss, idStr, ',');
                getline(ss, name, ',');
                getline(ss, wasteQuantityStr, ',');
                getline(ss, wasteCategory, ',');
                getline(ss, areaSizeStr, ',');
                getline(ss, location, ',');
                getline(ss, populationStr, ',');
                getline(ss, wasteManagementStrategy, ',');
                getline(ss, environmentalImpactStr, ',');
                getline(ss, budgetAllocatedStr, ',');
                getline(ss, lastUpdatedStr);

                // Convert strings to appropriate data types and add the area to the system
                int id = stoi(idStr);
                double wasteQuantity = stod(wasteQuantityStr);
                double areaSize = stod(areaSizeStr);
                int population = stoi(populationStr);
                double environmentalImpact = stod(environmentalImpactStr);
                double budgetAllocated = stod(budgetAllocatedStr);
                time_t lastUpdated = stoi(lastUpdatedStr); // Assuming the lastUpdated time is stored as a timestamp

                // Add the area using the parsed data
                addArea(id, name, wasteQuantity, wasteCategory, areaSize, location, population, lastUpdated,
                        wasteManagementStrategy, environmentalImpact, budgetAllocated);
            }
            cout << "Data loaded from " << filename << endl;
        } else {
            cout << "Error loading data from file.\n";
        }
    }

    // Method to calculate the total budget across all areas
    double calculateTotalBudget() const {
        double totalBudget = 0;
        // Loop through all areas and sum their allocated budgets
        for (const auto& entry : nodes) {
            totalBudget += entry.second.budgetAllocated;
        }
        return totalBudget;
    }

    // Display area with highest environmental impact
    void displayHighestEnvironmentalImpact() const {
        double highestImpact = -1;
        Area highestImpactArea;
        // Loop through all areas to find the one with the highest environmental impact score
        for (const auto& entry : nodes) {
            double impact = entry.second.calculateEnvironmentalImpact();
            if (impact > highestImpact) {
                highestImpact = impact;
                highestImpactArea = entry.second;
            }
        }

        cout << "\nArea with highest environmental impact:\n";
        highestImpactArea.displayAreaInfo();
    }
};

// Main function to interact with the system and manage areas
void manageWasteAreas(Graph &g) {
    // Adding areas to the graph for demonstration
    g.addArea(1, "Tilakwadi", 1200.0, "Plastic", 8.5, "Bel,Kar", 15000, time(0), "Recycling", 85.0, 50000);
    g.addArea(2, "Shivaji Nagar", 950.0, "Organic", 6.2, "Bel,Kar", 12000, time(0), "Composting", 75.0, 40000);
    g.addArea(3, "Camp", 2000.0, "Electronic", 12.0, "Bel,Kar", 18000, time(0), "Disposal", 90.0, 75000);
    g.addArea(4, "Raviwar Peth", 800.0, "Plastic", 5.5, "Bel,Kar", 10000, time(0), "Recycling", 70.0, 30000);
    g.addArea(5, "Khanapur Road", 1500.0, "Organic", 10.0, "Bel,Kar", 20000, time(0), "Composting", 80.0, 60000);
    g.addArea(6, "Maratha Colony", 600.0, "Plastic", 4.8, "Bel,Kar", 8000, time(0), "Recycling", 65.0, 25000);
    g.addArea(7, "Shahapur", 2200.0, "Electronic", 14.0, "Bel,Kar", 25000, time(0), "Disposal", 95.0, 100000);
    g.addArea(8, "Angol", 700.0, "Organic", 5.0, "Bel,Kar", 11000, time(0), "Composting", 72.0, 35000);
    g.addArea(9, "Vivekanand Nagar", 1800.0, "Plastic", 9.0, "Bel,Kar", 17000, time(0), "Recycling", 88.0, 65000);
    g.addArea(10, "Ramteerth Nagar", 2500.0, "Electronic", 15.0, "Bel,Kar", 30000, time(0), "Disposal", 92.0, 125000);


    int choice;
    do {
        // Display menu for user to choose operations
        cout << "\nMenu:\n";
        cout << "1. Display all areas\n";
        cout << "2. Sort areas by waste quantity\n";
        cout << "3. Display areas by waste category\n";
        cout << "4. Update area data\n";
        cout << "5. Delete area\n";
        cout << "6. Save data to file\n";
        cout << "7. Load data from file\n";
        cout << "8. Calculate total budget\n";
        cout << "9. Display area with highest environmental impact\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Switch case to handle the user's choice
        switch (choice) {
            case 1:
                g.displayAreas(); // Display all areas
                break;
            case 2:
                g.sortAreasByWaste(); // Sort areas by waste quantity
                cout << "Areas sorted by waste quantity.\n";
                break;
            case 3: {
                string category;
                cout << "Enter waste category: ";
                cin.ignore();
                getline(cin, category); // Get waste category from user
                g.displayAreasByCategory(category); // Display areas by waste category
                break;
            }
            case 4: {
                int id;
                cout << "Enter area ID to update: ";
                cin >> id; // Get area ID to update from user
                g.updateAreaData(id); // Update area data
                break;
            }
            case 5: {
                int id;
                cout << "Enter area ID to delete: ";
                cin >> id; // Get area ID to delete from user
                g.deleteArea(id); // Delete area by ID
                break;
            }
            case 6: {
                string filename;
                cout << "Enter filename to save data: ";
                cin >> filename; // Get filename to save data
                g.saveToFile(filename); // Save data to file
                break;
            }
            case 7: {
                string filename;
                cout << "Enter filename to load data: ";
                cin >> filename; // Get filename to load data
                g.loadFromFile(filename); // Load data from file
                break;
            }
            case 8: {
                double totalBudget = g.calculateTotalBudget(); // Calculate the total budget
                cout << "Total budget allocated across all areas: " << totalBudget << endl;
                break;
            }
            case 9:
                g.displayHighestEnvironmentalImpact(); // Display area with highest environmental impact
                break;
            case 10:
                cout << "Exiting program...\n"; // Exit the program
                break;
            default:
                cout << "Invalid option! Try again.\n"; // Handle invalid option
                break;
        }

    } while (choice != 10); // Continue until user chooses to exit
}


//module2

#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

// Define a structure to store area information
struct Areas {
    string name;
    vector<pair<int, int>> roads;  // {destination, distance}
};

// Number of areas
const int N = 10;
Areas areas[N];

// Truck capacity (in units of waste)
const int TRUCK_CAPACITY = 100;

// Function to find shortest paths using Dijkstra's Algorithm
void dijkstra(int start, vector<int>& dist) {
    dist.assign(N, INT_MAX);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& road : areas[u].roads) {
            int v = road.first;
            int weight = road.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// Function to collect waste and send trucks based on capacity
void collectWaste(int start, vector<int>& waste) {
    vector<int> dist(N, INT_MAX);
    dijkstra(start, dist);
    int totalWasteCollected = 0;
    int truckCount = 0;

    cout << "Waste collection starting from " << areas[start].name << ":\n";
    for (int i = 0; i < N; ++i) {
        if (dist[i] == INT_MAX) {
            cout << areas[i].name << ": Not accessible\n";
        } else {
            totalWasteCollected += waste[i];
            while (totalWasteCollected > (truckCount + 1) * TRUCK_CAPACITY) {
                truckCount++;
                cout << "Truck " << truckCount << " dispatched for area " << areas[i].name << " to collect waste.\n";
            }
            cout << areas[i].name << ": " << waste[i] << " units collected\n";
        }
    }
}

// Main function
int simulateWasteManagement() {
    // Example area names
    areas[0].name = "Tilakwadi";
    areas[1].name = "Shivaji Nagar";
    areas[2].name = "Camp";
    areas[3].name = "Raviwar Peth";
    areas[4].name = "Khanapur Road";
    areas[5].name = "Maratha Colony";
    areas[6].name = "Shahapur";
    areas[7].name = "Angol";
    areas[8].name = "Vivekanand Nagar";
    areas[9].name = "Ramteerth Nagar";

    // Example roads (area1, area2, distance)
    areas[0].roads = {{1, 10}, {2, 15}, {3, 35}, {4, 45}, {5, 85}, {6, 130}, {7, 180}, {8, 235}, {9, 295}};
    areas[1].roads = {{0, 10}, {2, 5}, {3, 25}, {4, 55}, {5, 95}, {6, 125}, {7, 180}, {8, 230}, {9, 280}};
    // More roads defined similarly...

    // Example waste to be collected from each area
    vector<int> waste = {50, 75, 20, 30, 60, 40, 80, 70, 90, 100}; // waste in units

    // Menu for interacting with the program
    int choice;
    do {
        cout << "\nMenu: \n";
        cout << "1. Show Shortest Paths\n";
        cout << "2. Close Road\n";
        cout << "3. Waste Collection using Trucks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int start;
                cout << "Enter the start area (0-9): ";
                cin >> start;
                vector<int> dist;
                dijkstra(start, dist);
                cout << "Shortest paths from area " << areas[start].name << ":\n";
                for (int i = 0; i < N; ++i) {
                    if (dist[i] == INT_MAX) {
                        cout << areas[i].name << ": Not accessible\n";
                    } else {
                        cout << areas[i].name << ": " << dist[i] << " units\n";
                    }
                }
                break;
            }

            case 2: {
                int u, v;
                cout << "Enter the two areas (0-9) to close the road between (u, v): ";
                cin >> u >> v;
                // Code to close the road between u and v (remove edges) can be added here
                cout << "Road closed between " << areas[u].name << " and " << areas[v].name << ".\n";
                break;
            }

            case 3: {
                int start;
                cout << "Enter the start area (0-9) for waste collection: ";
                cin >> start;
                collectWaste(start, waste);
                break;
            }

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}



//module3
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <ctime>
#include <functional>
#include <chrono>  // For std::chrono
#include <thread>  // For std::this_thread
#include <utility>  // For std::pair



//#include "classifyWaste.h"

// Function to classify waste based on input string
std::string classifyWaste(const std::string& waste)
{
    std::string lowerWaste = waste;
    for (auto& c : lowerWaste) c = tolower(c);

    if (lowerWaste.find("plastic") != std::string::npos)
    {
        return "Recyclable";
    }
    if (lowerWaste.find("glass") != std::string::npos)
    {
        return "Recyclable";
    }
    if (lowerWaste.find("metal") != std::string::npos)
    {
        return "Recyclable";
    }
    if (lowerWaste.find("paper") != std::string::npos)
    {
        return "Recyclable";
    }
    if (lowerWaste.find("food") != std::string::npos)
    {
        return "Biodegradable";
    }
    if (lowerWaste.find("plant") != std::string::npos)
    {
        return "Biodegradable";
    }
    if (lowerWaste.find("organic") != std::string::npos)
    {
        return "Biodegradable";
    }
    if (lowerWaste.find("batteries") != std::string::npos)
    {
        return "Non-Recyclable";
    }
    if (lowerWaste.find("chemical") != std::string::npos)
    {
        return "Non-Recyclable";
    }
    if (lowerWaste.find("plastic wrapper") != std::string::npos)
    {
        return "Non-Recyclable";
    }
    if (lowerWaste.find("inorganic") != std::string::npos)
    {
        return "Non-Biodegradable";
    }
    if (lowerWaste.find("electronics") != std::string::npos)
    {
        return "Electronic Waste";
    }
    if (lowerWaste.find("used electronics") != std::string::npos)
    {
        return "Non-Biodegradable";
    }
    if (lowerWaste.find("e-waste") != std::string::npos)
    {
        return "Electronic Waste";
    }
     if (lowerWaste.find("e-waste") != std::string::npos)
    {
        return "Non-Recyclable";
    }
    if (lowerWaste.find("hazardous") != std::string::npos)

    {
        return "Hazardous Waste";
    }
       if (lowerWaste.find("hazardous") != std::string::npos)

    {
        return "Non-Recyclable";
    }
    return "Non-Recyclable";
}

// Function to display waste items in tabular form
void displayWasteItems(const std::vector<std::string>& wasteItems)
{
    std::cout << "\nWaste Items in the System:\n";
    std::cout << std::setw(40) << std::left << "Waste Item"
              << std::setw(20) << std::left << "Classification"
              << "\n";
    std::cout << std::string(60, '-') << "\n";
    for (const auto& item : wasteItems)
    {
        std::cout << std::setw(40) << std::left << item
                  << std::setw(20) << std::left << classifyWaste(item)
                  << "\n";
    }
}



// Function to simulate SQL-like input data
std::vector<std::string> simulateSQLData()
{
    return
    {
        "Plastic Bottle",
        "Glass Jar",
        "Metal Can",
        "Paper Bag",
        "Food Waste",
        "Plant Leaves",
        "Inorganic Chemical",
        "Plastic Wrapper",
        "Old Newspaper",
        "Broken Toy",
        "Banana Peel",
        "Organic Compost",
        "Used Batteries",
        "Plastic Straw",
        "Old Computer",
        "TV Screen",
        "E-Waste",
        "Hazardous Chemical",
        "Used Electronics"
    };
}



#include <algorithm>
#include <cctype>



// Helper function to perform case-insensitive string comparison


bool equalsInsensitive(const std::string& str1, const std::string& str2) {
    std::string s1 = str1;
    std::string s2 = str2;
    std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    return s1 == s2;
}



// Function to classify hazardous items and prevent them from being marked as recyclable


bool isHazardous(const std::string& item) {
    if (item.find("Used Batteries") != std::string::npos || item.find("Hazardous Chemical") != std::string::npos || item.find("Used Electronics") != std::string::npos || item.find("E-Waste") != std::string::npos) {
        return true; // Mark items related to batteries or chemicals as hazardous
    }
    return false;
}

void sendToFactory(const std::map<std::string, std::string>& classifications)
{
    std::cout << "\n--- Journey to the Recycling Factory Begins! ---\n";

    bool foundRecyclable = false;
    int itemCount = 0; // Counter for recyclable items



    // Simulating the inspection process


    std::cout << "Inspector Bot is scanning the items...\n";
    for (const auto& entry : classifications)
    {
        std::cout << "Inspecting: " << entry.first << " - Classified as: " << entry.second << "\n";

        // Check if item is hazardous (e.g., battery or chemical)


        if (isHazardous(entry.first)) {
            std::cout << entry.first << " is hazardous and cannot be recycled. Moving to the next item.\n";
            continue; // Skip hazardous items
        }

        // Case-insensitive check for recyclability


        if (equalsInsensitive(entry.second, "recyclable"))
        {
            ++itemCount;
            std::cout << entry.first << " is recyclable! Preparing to send it to the factory.\n";
            foundRecyclable = true;
        } else
        {
            std::cout << entry.first << " is not recyclable. Moving to the next item.\n";
        }
    }

    if (foundRecyclable)
    {
        std::cout << "\n--- Sending the Recyclable Items to the Factory ---\n";
        for (const auto& entry : classifications)
        {
            if (equalsInsensitive(entry.second, "recyclable") && !isHazardous(entry.first))
            {
                std::cout << "Loading " << entry.first << " onto the recycling truck.\n";
            }
        }
        std::cout << "\nSuccess! " << itemCount << " items have been dispatched for recycling. Let's save the planet!\n";
    } else
    {
        std::cout << "\nOh no! No recyclable items were found. Please review the classifications and try again.\n";
    }

    std::cout << "\n--- End of Simulation. Thank you for recycling responsibly! ---\n";
}



// Function to simulate selling recyclable materials


void sendToSell(const std::map<std::string, std::string>& classifications) {
    std::cout << "\n---  Welcome to the Market Adventure! ---\n";

    bool foundSellable = false;
    int sellableCount = 0; // Counter for sellable items

    std::cout << "\n Starting Inspection Process for Market: \n";
    for (const auto& entry : classifications)
    {
        std::cout << "Inspecting item: " << entry.first << " - Classification: " << entry.second << "\n";

        if (entry.second == "Recyclable" && entry.second == "Biodegradable")
        {
            sellableCount++;
            std::cout << "Excellent! " << entry.first << " is sellable. Adding it to the market queue.\n";
            foundSellable = true;
        } else
        {
            std::cout << " \n\nUnfortunately, " << entry.first << " is not suitable for selling. Redirecting it elsewhere.\n";
        }
    }

    if (foundSellable)
    {
        std::cout << "\n---  Dispatching Sellable Items to the Market ---\n";
        for (const auto& entry : classifications)
        {
            if (entry.second == "Recyclable" && entry.second == "Biodegradable") {
                std::cout << " Preparing " << entry.first << " for transport to the market.\n";
            }


        }
        std::cout << "\n Success! " << sellableCount << " items have been successfully dispatched to the market.\n";
        std::cout << "Thank you for contributing to a sustainable economy! \n";
    } else
    {
        std::cout << "\n Alert! No sellable items were found. Please review the item classifications and try again.\n";
    }

    std::cout << "\n---  End of Market Adventure. Keep Promoting Sustainability!  ---\n";
}



#include <iostream>
#include <map>
#include <vector>
#include <ctime>

// Function to simulate burning non-recyclable materials


void sendToBurn(const std::map<std::string, std::string>& classifications)
{
    std::cout << "\n--- Sending Burnable Products to Incinerator ---\n";

    bool foundBurnable = false;
    int totalItems = classifications.size();
    int itemsSent = 0;
    std::vector<std::string> burnableItems;

    // Displaying the initial state of the classifications


    std::cout << "Total items in classification: " << totalItems << "\n";
    std::cout << "Checking each item for burnable classification...\n\n";

    // Process each item in the classifications map


    for (const auto& entry : classifications)
    {
        const std::string& item = entry.first;
        const std::string& classification = entry.second;

        // Check if the item is classified as Non-Recyclable or Non-Biodegradable


        if (classification == "Non-Recyclable" || classification == "Non-Biodegradable" || classification == "Hazardous")
        {
            std::cout << "Found " << item << " as " << classification << " -> Sending to incinerator.\n";
            burnableItems.push_back(item);
            foundBurnable = true;
            itemsSent++;
        }
        else
        {
            std::cout << item << " is " << classification << " -> Not for burning.\n";
        }
    }

    // Display summary of the burning process

    if (!foundBurnable)
    {
        std::cout << "\nNo burnable products found. All items are either recyclable or biodegradable.\n";
    } else {
        std::cout << "\nTotal burnable items found: " << itemsSent << "\n";
        std::cout << "Items being sent to the incinerator:\n";
        for (const std::string& item : burnableItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting non-burnable items (optional)

    int nonBurnableItems = totalItems - itemsSent;
    std::cout << "\nTotal non-burnable items: " << nonBurnableItems << "\n";

    // Detailed report


    // Cleanup message
    std::cout << "\nBurning process complete. Items classified and sent accordingly.\n";
}

// Function to simulate destroying hazardous waste with added checks and reports

// Utility function to get current timestamp

std::string getCurrentTime() {
    std::time_t currentTime = std::time(nullptr);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
    return buffer;
}



// Function to simulate destroying hazardous waste


void sendToDestroy(const std::map<std::string, std::string>& classifications)
{
    std::cout << "\n--- Sending Hazardous Waste to Destruction Facility ---\n";

    bool foundHazardous = false;
    int totalItems = classifications.size();
    int itemsSent = 0;
    std::vector<std::string> hazardousItems;
    std::vector<std::string> nonHazardousItems;

    // Logging start time
    std::cout << "Process started at: " << getCurrentTime() << "\n";
    std::cout << "Total items to process: " << totalItems << "\n";

    // Begin processing items
    std::cout << "\nChecking each item for hazardous classification...\n\n";

    // Process each item in the map
    for (const auto& entry : classifications)
    {
        const std::string& item = entry.first;
        const std::string& classification = entry.second;

        std::cout << "[Checking] Item: " << item << " | Classification: " << classification << "\n";

        // Check if the item is hazardous waste
        if (classification == "Hazardous Waste")
        {
            std::cout << "[Found] " << item << " classified as Hazardous Waste. Sending to destruction facility.\n";
            hazardousItems.push_back(item);
            foundHazardous = true;
            itemsSent++;
        }
        else if (classification == "Recyclable")
        {
            std::cout << "[Safe] " << item << " is recyclable. Not hazardous.\n";
            nonHazardousItems.push_back(item);
        }
        else if (classification == "Biodegradable")
        {
            std::cout << "[Safe] " << item << " is biodegradable. Not hazardous.\n";
            nonHazardousItems.push_back(item);
        }
        else
        {
            std::cout << "[Unclassified] " << item << " has an unknown classification. Further investigation needed.\n";
        }
    }

    // If no hazardous waste found, report it


    if (!foundHazardous)
    {
        std::cout << "\nNo hazardous waste found. All items are safe for regular disposal.\n";
    } else
    {
        std::cout << "\nTotal hazardous waste items: " << itemsSent << "\n";
        std::cout << "Items being sent to the destruction facility:\n";
        for (const std::string& item : hazardousItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting non-hazardous items


    int nonHazardousItemsCount = nonHazardousItems.size();
    std::cout << "\nTotal non-hazardous items: " << nonHazardousItemsCount << "\n";
    std::cout << "Non-hazardous items processed (Recyclable/Biodegradable):\n";
    for (const std::string& item : nonHazardousItems)

    {
        std::cout << "- " << item << "\n";
    }

    // Detailed report: Provide a comprehensive report of all classifications



    std::cout << "\n--- Detailed Classification Report ---\n";
    for (const auto& entry : classifications)
    {
        const std::string& item = entry.first;
        const std::string& classification = entry.second;
        std::cout << "[Item] " << item << " | [Classification] " << classification << "\n";
    }

    // Simulating the process of destruction


    std::cout << "\n--- Destruction Process Initiating ---\n";
    std::cout << "All hazardous materials are being securely destroyed...\n";

    // Simulate delay in destruction process (to represent time)


    for (int i = 0; i < 3; ++i)

    {
        std::cout << "Destruction in progress. Remaining items: " << hazardousItems.size() - i << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nDestruction complete. All hazardous materials are safely destroyed.\n";

    // Log the time the process ended


    std::cout << "Process completed at: " << getCurrentTime() << "\n";

    // Cleanup and summary report


    std::cout << "\n--- Final Summary Report ---\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Hazardous items destroyed: " << itemsSent << "\n";
    std::cout << "Non-hazardous items processed: " << nonHazardousItemsCount << "\n";
    std::cout << "Process completed successfully.\n";
}



#include <algorithm>
#include <cctype>

// Helper function to perform case-insensitive string comparison


bool containsInsensitive(const std::string& haystack, const std::string& needle) {
    std::string haystackLower = haystack;
    std::string needleLower = needle;

    std::transform(haystackLower.begin(), haystackLower.end(), haystackLower.begin(), ::tolower);
    std::transform(needleLower.begin(), needleLower.end(), needleLower.begin(), ::tolower);

    return haystackLower.find(needleLower) != std::string::npos;
}

void preliminaryInspection(const std::vector<std::string>& wasteItems)
{
    std::cout << "\n--- Preliminary Inspection Phase ---\n";

    int totalItems = wasteItems.size();
    int hazardousFound = 0;
    int safeItems = 0;
    int unclassifiedItems = 0;

    std::cout << "Inspection started at: " << getCurrentTime() << "\n";
    std::cout << "Total items to inspect: " << totalItems << "\n\n";

    std::vector<std::string> hazardousItems;
    std::vector<std::string> safeItemsList;
    std::vector<std::string> unclassifiedItemsList;

    // Processing each item in the wasteItems vector


    for (const auto& item : wasteItems)
    {
        std::cout << "[Inspecting] Item: " << item << "\n";

        // Check for hazardous materials (e.g., batteries, chemicals) using case-insensitive matching


        if (containsInsensitive(item, "used batteries") || containsInsensitive(item, "hazardous chemical"))
        {
            std::cout << "Hazardous Item Found: " << item << " - Segregated for safe disposal.\n";
            hazardousItems.push_back(item);
            hazardousFound++;
        }
        // Check for unclassified items


        else if (containsInsensitive(item, "unknown") || containsInsensitive(item, "unidentified"))
        {
            std::cout << "Unclassified Item Found: " << item << " - Needs further investigation.\n";
            unclassifiedItemsList.push_back(item);
            unclassifiedItems++;
        }
        // Safe items


        else {
            std::cout << "Inspected: " << item << " - No hazards detected.\n";
            safeItemsList.push_back(item);
            safeItems++;
        }
    }

    // Summary of findings


    std::cout << "\nInspection complete at: " << getCurrentTime() << "\n";
    std::cout << "Total items inspected: " << totalItems << "\n";
    std::cout << "Hazardous items found: " << hazardousFound << "\n";
    std::cout << "Safe items found: " << safeItems << "\n";
    std::cout << "Unclassified items: " << unclassifiedItems << "\n";

    // Reporting hazardous items


    if (!hazardousItems.empty())
    {
        std::cout << "\n--- Hazardous Items ---\n";
        for (const auto& item : hazardousItems) {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting unclassified items


    if (!unclassifiedItemsList.empty())
    {
        std::cout << "\n--- Unclassified Items ---\n";
        for (const auto& item : unclassifiedItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting safe items


    if (!safeItemsList.empty())
    {
        std::cout << "\n--- Safe Items ---\n";
        for (const auto& item : safeItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Final summary message


    std::cout << "\nInspection process complete. Segregation of hazardous, unclassified, and safe items done successfully.\n";
}


#include <iostream>
#include <vector>
#include <string>
#include <ctime>




// Function to simulate manual sorting of waste items


void manualSorting(const std::vector<std::string>& wasteItems)
{
    std::cout << "\n--- Manual Sorting Phase ---\n";

    // Logging start time


    std::cout << "Sorting started at: " << getCurrentTime() << "\n";
    int totalItems = wasteItems.size();
    int recyclableItems = 0;
    int nonRecyclableItems = 0;
    int hazardousItems = 0;
    int biodegradableItems = 0;

    // Vectors to hold sorted items


    std::vector<std::string> recyclable, nonRecyclable, hazardous, biodegradable;

    // Sorting items into appropriate categories


    for (const auto& item : wasteItems)
    {
        std::cout << "[Sorting] Item: " << item << "...\n";

        // Clearer rules for recyclable items


        if (item == "Plastic Bottle" || item == "Glass Jar" || item == "Metal Can" ||
            item == "Old Newspaper" || item == "Plastic Straw" || item == "Old Computer" ||
            item == "TV Screen" || item == "E-Waste" || item == "Used Electronics")
        {
            recyclable.push_back(item);
            recyclableItems++;
            std::cout << "- Classified as recyclable.\n";
        }
        // Non-recyclable items


        else if (item == "Plastic Wrapper" || item == "Broken Toy" || item == "Styrofoam")
        {
            nonRecyclable.push_back(item);
            nonRecyclableItems++;
            std::cout << "- Classified as non-recyclable.\n";
        }
        // Hazardous items
        else if (item == "Used Batteries" || item == "Hazardous Chemical" || item == "Inorganic Chemical")
        {
            hazardous.push_back(item);
            hazardousItems++;
            std::cout << "- Classified as hazardous.\n";
        }
        // Biodegradable items
        else if (item == "Food Waste" || item == "Plant Leaves" || item == "Banana Peel" ||
                 item == "Organic Compost" || item == "Paper Bag")
        {
            biodegradable.push_back(item);
            biodegradableItems++;
            std::cout << "- Classified as biodegradable.\n";
        }
        else {
            std::cout << "- Unclassified item. Needs further inspection.\n";
        }
    }

    // Provide a summary of sorting


    std::cout << "\nSorting completed at: " << getCurrentTime() << "\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Recyclable items: " << recyclableItems << "\n";
    std::cout << "Non-recyclable items: " << nonRecyclableItems << "\n";
    std::cout << "Hazardous items: " << hazardousItems << "\n";
    std::cout << "Biodegradable items: " << biodegradableItems << "\n";

    // Reporting sorted items


    std::cout << "\n--- Recyclable Items ---\n";
    for (const auto& item : recyclable)
    {
        std::cout << "- " << item << "\n";
    }

    std::cout << "\n--- Non-Recyclable Items ---\n";
    for (const auto& item : nonRecyclable)
    {
        std::cout << "- " << item << "\n";
    }

    std::cout << "\n--- Hazardous Items ---\n";
    for (const auto& item : hazardous)
    {
        std::cout << "- " << item << "\n";
    }

    std::cout << "\n--- Biodegradable Items ---\n";
    for (const auto& item : biodegradable)
    {
        std::cout << "- " << item << "\n";
    }

    // Final summary message
    std::cout << "\nSorting process complete. All items have been categorized for disposal.\n";
}
// Function to simulate mechanical sorting of waste items
void mechanicalSorting(const std::vector<std::string>& wasteItems)
{
    std::cout << "\n--- Mechanical Sorting Phase ---\n";

    // Logging start time
    std::cout << "Sorting started at: " << getCurrentTime() << "\n";

    int totalItems = wasteItems.size();
    int plasticItems = 0;
    int glassItems = 0;
    int metalItems = 0;
    int otherItems = 0;

    // Vectors to hold processed items
    std::vector<std::string> plasticItemsList, glassItemsList, metalItemsList, otherItemsList;

    // Processing each item in the wasteItems vector
    for (const auto& item : wasteItems)

    {
        std::cout << "[Processing] Item: " << item << "...\n";

        // Check if the item is plastic
        if (item.find("plastic") != std::string::npos)
        {
            std::cout << "Shredding and screening: " << item << " (Plastic)\n";
            plasticItems++;
            plasticItemsList.push_back(item);
        }
        // Check if the item is glass
        else if (item.find("glass") != std::string::npos)
        {
            std::cout << "Shredding and screening: " << item << " (Glass)\n";
            glassItems++;
            glassItemsList.push_back(item);
        }
        // Check if the item is metal
        else if (item.find("metal") != std::string::npos)
        {
            std::cout << "Shredding and screening: " << item << " (Metal)\n";
            metalItems++;
            metalItemsList.push_back(item);
        }
        // For items that don't require mechanical processing
        else
        {
            std::cout << "No mechanical processing required: " << item << " (Other)\n";
            otherItems++;
            otherItemsList.push_back(item);
        }
    }

    // Provide a detailed summary of the mechanical sorting process
    std::cout << "\nSorting completed at: " << getCurrentTime() << "\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Plastic items: " << plasticItems << "\n";
    std::cout << "Glass items: " << glassItems << "\n";
    std::cout << "Metal items: " << metalItems << "\n";
    std::cout << "Other items: " << otherItems << "\n";

    // Reporting sorted plastic items
    if (!plasticItemsList.empty()) {
        std::cout << "\n--- Plastic Items ---\n";
        for (const auto& item : plasticItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting sorted glass items
    if (!glassItemsList.empty())
    {
        std::cout << "\n--- Glass Items ---\n";
        for (const auto& item : glassItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting sorted metal items
    if (!metalItemsList.empty())
    {
        std::cout << "\n--- Metal Items ---\n";
        for (const auto& item : metalItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting unprocessed or unclassified items
    if (!otherItemsList.empty())
    {
        std::cout << "\n--- Unprocessed/Other Items ---\n";
        for (const auto& item : otherItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Simulate processing steps for plastic, glass, and metal
    std::cout << "\n--- Mechanical Processing in Progress ---\n";

    // Now initializing allItems as a vector of vectors
    std::vector<std::vector<std::string>> allItems = {plasticItemsList, glassItemsList, metalItemsList, otherItemsList};

    for (size_t i = 0; i < allItems.size(); ++i)
    {
        std::cout << "[Shredding and Screening] Processing items batch " << i + 1 << "...\n";
        for (const auto& item : allItems[i])
        {
            std::cout << "Processing item: " << item << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Simulating delay
        }
    }

    // Final report after processing
    std::cout << "\n--- Final Summary ---\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Plastic items shredded: " << plasticItems << "\n";
    std::cout << "Glass items shredded: " << glassItems << "\n";
    std::cout << "Metal items shredded: " << metalItems << "\n";
    std::cout << "Unprocessed items: " << otherItems << "\n";

    std::cout << "\nMechanical sorting completed successfully.\n";
}


// Function to simulate advanced sorting of waste items
void advancedSorting(const std::vector<std::string>& wasteItems)
{
    std::cout << "\n--- Advanced Sorting Phase ---\n";

    // Logging the start time
    std::cout << "Sorting started at: " << getCurrentTime() << "\n";

    int totalItems = wasteItems.size();
    int plasticItems = 0;
    int glassItems = 0;
    int metalItems = 0;
    int unprocessedItems = 0;

    // Vectors to hold processed items
    std::vector<std::string> plasticItemsList, glassItemsList, metalItemsList, unprocessedItemsList;

    // Processing each item in the wasteItems vector
    for (const auto& item : wasteItems)
    {
        std::cout << "[Processing] Item: " << item << "...\n";

        // Check if the item is plastic
        if (item.find("plastic") != std::string::npos)
        {
            plasticItems++;
            plasticItemsList.push_back(item);
            std::cout << "Optical sorting applied: " << item << " (Plastic)\n";
        }
        // Check if the item is glass
        else if (item.find("glass") != std::string::npos)

        {
            glassItems++;
            glassItemsList.push_back(item);
            std::cout << "Optical sorting applied: " << item << " (Glass)\n";
        }
        // Check if the item is metal
        else if (item.find("metal") != std::string::npos)
        {
            metalItems++;
            metalItemsList.push_back(item);
            std::cout << "Eddy current separation applied: " << item << " (Metal)\n";
        }
        // For items that don't require advanced sorting
        else
        {
            unprocessedItems++;
            unprocessedItemsList.push_back(item);
            std::cout << "No advanced sorting required: " << item << " (Unprocessed)\n";
        }
    }

    // Provide a detailed summary of the advanced sorting process
    std::cout << "\nSorting completed at: " << getCurrentTime() << "\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Plastic items sorted: " << plasticItems << "\n";
    std::cout << "Glass items sorted: " << glassItems << "\n";
    std::cout << "Metal items sorted: " << metalItems << "\n";
    std::cout << "Unprocessed items: " << unprocessedItems << "\n";

    // Reporting sorted plastic items
    if (!plasticItemsList.empty())
    {
        std::cout << "\n--- Plastic Items ---\n";
        for (const auto& item : plasticItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting sorted glass items
    if (!glassItemsList.empty()) {
        std::cout << "\n--- Glass Items ---\n";
        for (const auto& item : glassItemsList)

        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting sorted metal items
    if (!metalItemsList.empty())
    {
        std::cout << "\n--- Metal Items ---\n";
        for (const auto& item : metalItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting unprocessed or unclassified items
    if (!unprocessedItemsList.empty())
    {
        std::cout << "\n--- Unprocessed Items ---\n";
        for (const auto& item : unprocessedItemsList)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Simulate the advanced sorting processing
    std::cout << "\n--- Advanced Sorting Processing ---\n";

    // Initialize allItems as a vector of vectors
    std::vector<std::vector<std::string>> allItems = {plasticItemsList, glassItemsList, metalItemsList, unprocessedItemsList};

    for (size_t i = 0; i < allItems.size(); ++i)

    {
        std::cout << "[Processing] Sorting batch " << i + 1 << "...\n";
        for (const auto& item : allItems[i])
        {
            std::cout << "Processing item: " << item << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));  // Simulating delay for processing
        }
    }

    // Final report after sorting
    std::cout << "\n--- Final Summary ---\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Plastic items sorted: " << plasticItems << "\n";
    std::cout << "Glass items sorted: " << glassItems << "\n";
    std::cout << "Metal items sorted: " << metalItems << "\n";
    std::cout << "Unprocessed items: " << unprocessedItems << "\n";

    std::cout << "\nAdvanced sorting completed successfully.\n";
}


// Function to handle additional waste categories such as Electronic Waste and Hazardous Waste
void handleAdditionalCategories(const std::map<std::string, std::string>& classifications)
{
    std::cout << "\n--- Handling Additional Categories ---\n";
    std::cout << "Processing started at: " << getCurrentTime() << "\n";

    int totalItems = classifications.size();
    int electronicWasteCount = 0;
    int hazardousWasteCount = 0;
    int otherWasteCount = 0;

    // Vectors to hold categorized items
    std::vector<std::string> electronicWasteItems;
    std::vector<std::string> hazardousWasteItems;
    std::vector<std::string> otherWasteItems;

    // Iterating over the classifications and processing each item
    for (const auto& entry : classifications)
    {
        std::cout << "[Processing] Item: " << entry.first << " - Category: " << entry.second << "\n";

        // Handling Electronic Waste
        if (entry.second == "Electronic Waste")
        {
            std::cout << "Item: " << entry.first << " is Electronic Waste - Sent to specialized e-waste facility.\n";
            electronicWasteCount++;
            electronicWasteItems.push_back(entry.first);
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Simulate delay
        }
        // Handling Hazardous Waste
        else if (entry.second == "Hazardous Waste")
        {
            std::cout << "Item: " << entry.first << " is Hazardous Waste - Proper disposal required.\n";
            hazardousWasteCount++;
            hazardousWasteItems.push_back(entry.first);
            std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Simulate delay
        }
        // For other waste categories
        else

        {
            otherWasteCount++;
            otherWasteItems.push_back(entry.first);
            std::cout << "Item: " << entry.first << " is categorized as Other Waste - Sending to general processing facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simulate delay
        }
    }



    // Report on categorized waste


    std::cout << "\nProcessing completed at: " << getCurrentTime() << "\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Electronic Waste items: " << electronicWasteCount << "\n";
    std::cout << "Hazardous Waste items: " << hazardousWasteCount << "\n";
    std::cout << "Other Waste items: " << otherWasteCount << "\n";

    // Reporting sorted electronic waste items


    if (!electronicWasteItems.empty())
    {
        std::cout << "\n--- Electronic Waste Items ---\n";
        for (const auto& item : electronicWasteItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting sorted hazardous waste items


    if (!hazardousWasteItems.empty())
    {
        std::cout << "\n--- Hazardous Waste Items ---\n";
        for (const auto& item : hazardousWasteItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Reporting other waste items


    if (!otherWasteItems.empty())
    {
        std::cout << "\n--- Other Waste Items ---\n";
        for (const auto& item : otherWasteItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Simulating the processing of each category of waste
    std::cout << "\n--- Processing Waste Categories ---\n";

    // Process Electronic Waste
    if (!electronicWasteItems.empty())
    {
        std::cout << "\nProcessing Electronic Waste...\n";
        for (const auto& item : electronicWasteItems)
        {
            std::cout << "Sending " << item << " to specialized e-waste facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));  // Simulating time for processing
        }
    }

    // Process Hazardous Waste
    if (!hazardousWasteItems.empty())
    {
        std::cout << "\nProcessing Hazardous Waste...\n";
        for (const auto& item : hazardousWasteItems)
        {
            std::cout << "Sending " << item << " to hazardous waste disposal facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(400));  // Simulating time for processing
        }
    }

    // Process Other Waste
    if (!otherWasteItems.empty())
    {
        std::cout << "\nProcessing Other Waste...\n";
        for (const auto& item : otherWasteItems)
        {
            std::cout << "Sending " << item << " to general processing facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Simulating time for processing
        }
    }

    // Final summary after all waste is processed


    std::cout << "\n--- Final Waste Processing Summary ---\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Electronic Waste items: " << electronicWasteCount << "\n";
    std::cout << "Hazardous Waste items: " << hazardousWasteCount << "\n";
    std::cout << "Other Waste items: " << otherWasteCount << "\n";

    std::cout << "\nWaste processing completed successfully.\n";
}


// Function to classify waste item based on predefined rules

// Function to classify waste items and populate the classifications map

void classifyWasteItems(std::vector<std::string>& wasteItems, std::map<std::string, std::string>& classifications)
{
    std::cout << "\n--- Classifying Waste Items ---\n";
    std::cout << "Classification started at: " << getCurrentTime() << "\n";

    int totalItems = wasteItems.size();
    int plasticCount = 0, glassCount = 0, metalCount = 0, hazardousCount = 0, electronicCount = 0, paperCount = 0, organicCount = 0, generalCount = 0;

    // Vectors to hold classified waste items
    std::vector<std::string> plasticItems, glassItems, metalItems, hazardousItems, electronicItems, paperItems, organicItems, generalItems;

    // Classifying each waste item and populating the map


    for (const auto& item : wasteItems)
    {
        std::string classification = classifyWaste(item);
        classifications[item] = classification;

        // Increment counters based on classification


        if (classification == "Plastic")
        {
            plasticCount++;
            plasticItems.push_back(item);
        }
        else if (classification == "Glass")
        {
            glassCount++;
            glassItems.push_back(item);
        }
        else if (classification == "Metal")
        {
            metalCount++;
            metalItems.push_back(item);
        }
        else if (classification == "Hazardous Waste")
        {
            hazardousCount++;
            hazardousItems.push_back(item);
        }
        else if (classification == "Electronic Waste") {
            electronicCount++;
            electronicItems.push_back(item);
        }
        else if (classification == "Paper") {
            paperCount++;
            paperItems.push_back(item);
        }
        else if (classification == "Organic Waste") {
            organicCount++;
            organicItems.push_back(item);
        }
        else {
            generalCount++;
            generalItems.push_back(item);
        }

        std::cout << "[Classifying] Item: " << item << " - Classified as: " << classification << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate processing delay
    }



    // Final report on classification process

    std::cout << "\nClassification completed at: " << getCurrentTime() << "\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Plastic items: " << plasticCount << "\n";
    std::cout << "Glass items: " << glassCount << "\n";
    std::cout << "Metal items: " << metalCount << "\n";
    std::cout << "Hazardous Waste items: " << hazardousCount << "\n";
    std::cout << "Electronic Waste items: " << electronicCount << "\n";
    std::cout << "Paper items: " << paperCount << "\n";
    std::cout << "Organic Waste items: " << organicCount << "\n";
    std::cout << "General Waste items: " << generalCount << "\n";

    // Reporting classified waste items


    if (!plasticItems.empty()) {
        std::cout << "\n--- Plastic Items ---\n";
        for (const auto& item : plasticItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!glassItems.empty()) {
        std::cout << "\n--- Glass Items ---\n";
        for (const auto& item : glassItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!metalItems.empty()) {
        std::cout << "\n--- Metal Items ---\n";
        for (const auto& item : metalItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!hazardousItems.empty()) {
        std::cout << "\n--- Hazardous Waste Items ---\n";
        for (const auto& item : hazardousItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!electronicItems.empty()) {
        std::cout << "\n--- Electronic Waste Items ---\n";
        for (const auto& item : electronicItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!paperItems.empty()) {
        std::cout << "\n--- Paper Items ---\n";
        for (const auto& item : paperItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!organicItems.empty()) {
        std::cout << "\n--- Organic Waste Items ---\n";
        for (const auto& item : organicItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    if (!generalItems.empty()) {
        std::cout << "\n--- General Waste Items ---\n";
        for (const auto& item : generalItems)
        {
            std::cout << "- " << item << "\n";
        }
    }

    // Simulate processing each category


    std::cout << "\n--- Processing Waste Categories ---\n";

    // Process each waste category

    if (!plasticItems.empty())
    {
        std::cout << "\nProcessing Plastic Waste...\n";
        for (const auto& item : plasticItems)
        {
            std::cout << "Sending " << item << " to plastic recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(150));  // Simulate time for processing
        }
    }

    if (!glassItems.empty()) {
        std::cout << "\nProcessing Glass Waste...\n";
        for (const auto& item : glassItems)
        {
            std::cout << "Sending " << item << " to glass recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Simulate time for processing
        }
    }

    if (!metalItems.empty())
    {
        std::cout << "\nProcessing Metal Waste...\n";
        for (const auto& item : metalItems)
        {
            std::cout << "Sending " << item << " to metal recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(250));  // Simulate time for processing
        }
    }

    if (!hazardousItems.empty())
    {
        std::cout << "\nProcessing Hazardous Waste...\n";
        for (const auto& item : hazardousItems)
        {
            std::cout << "Sending " << item << " to hazardous waste disposal facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));  // Simulate time for processing
        }
    }

    if (!electronicItems.empty())
    {
        std::cout << "\nProcessing Electronic Waste...\n";
        for (const auto& item : electronicItems)
        {
            std::cout << "Sending " << item << " to electronic waste facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(350));  // Simulate time for processing
        }
    }

    if (!paperItems.empty())
    {
        std::cout << "\nProcessing Paper Waste...\n";
        for (const auto& item : paperItems)
        {
            std::cout << "Sending " << item << " to paper recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simulate time for processing
        }
    }

    if (!organicItems.empty())
    {
        std::cout << "\nProcessing Organic Waste...\n";
        for (const auto& item : organicItems)
        {
            std::cout << "Sending " << item << " to composting facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(150));  // Simulate time for processing
        }
    }

    if (!generalItems.empty())
    {
        std::cout << "\nProcessing General Waste...\n";
        for (const auto& item : generalItems)
        {
            std::cout << "Sending " << item << " to general landfill.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));  // Simulate time for processing
        }
    }

    // Final summary of all classifications and processing
    std::cout << "\nWaste Classification and Processing completed successfully.\n";
}


// Function to classify waste



void displayBiodegradableItems(const std::vector<std::string>& wasteItems) {
    std::cout << "\n--- Biodegradable Materials in the System ---\n";

    int totalItems = wasteItems.size();
    int biodegradableCount = 0;
    std::vector<std::string> biodegradableItems;
    std::vector<std::string> nonBiodegradableItems;

    // Logging start of process
    std::cout << "Process started...\n";
    std::cout << "Total waste items to process: " << totalItems << "\n";
    std::cout << std::string(50, '-') << "\n";

    // Start processing each item
    std::cout << "Processing biodegradable materials...\n";
    for (const auto& item : wasteItems) {
        std::string classification;

        // Classifying based on item name directly
        if (item == "Food Waste" || item == "Plant Leaves" || item == "Banana Peel" || item == "Organic Compost") {
            classification = "Biodegradable";
        } else {
            classification = "Non-Biodegradable";
        }

        std::cout << "[Checking] " << item << " | Classification: " << classification << "\n";

        // If the item is biodegradable, add it to the biodegradable list
        if (classification == "Biodegradable") {
            biodegradableItems.push_back(item);
            biodegradableCount++;
        } else {
            nonBiodegradableItems.push_back(item);
        }
    }

    // Reporting biodegradable materials
    std::cout << "\n--- Biodegradable Materials Found ---\n";
    if (biodegradableCount > 0) {
        std::cout << std::setw(40) << std::left << "Waste Item"
                  << std::setw(20) << std::left << "Classification"
                  << "\n";
        std::cout << std::string(60, '-') << "\n";

        for (const auto& item : biodegradableItems) {
            std::cout << std::setw(40) << std::left << item
                      << std::setw(20) << std::left << "Biodegradable"
                      << "\n";
        }
    } else {
        std::cout << "No biodegradable materials found in the input list.\n";
    }

    // Reporting non-biodegradable items


    std::cout << "\n--- Non-Biodegradable Materials ---\n";
    if (!nonBiodegradableItems.empty()) {
        std::cout << std::setw(40) << std::left << "Waste Item"
                  << std::setw(20) << std::left << "Classification"
                  << "\n";
        std::cout << std::string(60, '-') << "\n";
        for (const auto& item : nonBiodegradableItems) {
            std::cout << std::setw(40) << std::left << item
                      << std::setw(20) << std::left << "Non-Biodegradable"
                      << "\n";
        }
    } else {
        std::cout << "All items in the list are biodegradable!\n";
    }

    // Final logging and summary


    std::cout << "\n--- Process Summary ---\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Biodegradable items: " << biodegradableCount << "\n";
    std::cout << "Non-biodegradable items: " << nonBiodegradableItems.size() << "\n";
    std::cout << "Process completed successfully.\n";
}
void classifyWastebItems(std::vector<std::string>& wasteItems, std::map<std::string, std::string>& classifications) {
    std::cout << "\n--- Classifying Waste Items ---\n";
    std::cout << "Classification started at: " << getCurrentTime() << "\n";

    int totalItems = wasteItems.size();
    int plasticCount = 0, glassCount = 0, metalCount = 0, hazardousCount = 0, electronicCount = 0, paperCount = 0, organicCount = 0, generalCount = 0;

    // Vectors to hold classified waste items


    std::vector<std::string> plasticItems, glassItems, metalItems, hazardousItems, electronicItems, paperItems, organicItems, generalItems;

    // Classifying each waste item and populating the map

    for (const auto& item : wasteItems) {
        std::string classification = classifyWaste(item);
        classifications[item] = classification;

        // Increment counters based on classification


        if (classification == "Plastic") {
            plasticCount++;
            plasticItems.push_back(item);
        }
        else if (classification == "Glass") {
            glassCount++;
            glassItems.push_back(item);
        }
        else if (classification == "Metal") {
            metalCount++;
            metalItems.push_back(item);
        }
        else if (classification == "Hazardous Waste") {
            hazardousCount++;
            hazardousItems.push_back(item);
        }
        else if (classification == "Electronic Waste") {
            electronicCount++;
            electronicItems.push_back(item);
        }
        else if (classification == "Paper") {
            paperCount++;
            paperItems.push_back(item);
        }
        else if (classification == "Organic Waste") {
            organicCount++;
            organicItems.push_back(item);
        }
        else {
            generalCount++;
            generalItems.push_back(item);
        }

        std::cout << "[Classifying] Item: " << item << " - Classified as: " << classification << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate processing delay
    }

    // Final report on classification process


    std::cout << "\nClassification completed at: " << getCurrentTime() << "\n";
    std::cout << "Total items processed: " << totalItems << "\n";
    std::cout << "Plastic items: " << plasticCount << "\n";
    std::cout << "Glass items: " << glassCount << "\n";
    std::cout << "Metal items: " << metalCount << "\n";
    std::cout << "Hazardous Waste items: " << hazardousCount << "\n";
    std::cout << "Electronic Waste items: " << electronicCount << "\n";
    std::cout << "Paper items: " << paperCount << "\n";
    std::cout << "Organic Waste items: " << organicCount << "\n";
    std::cout << "General Waste items: " << generalCount << "\n";

    // Reporting classified waste items


    if (!plasticItems.empty()) {
        std::cout << "\n--- Plastic Items ---\n";
        for (const auto& item : plasticItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!glassItems.empty()) {
        std::cout << "\n--- Glass Items ---\n";
        for (const auto& item : glassItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!metalItems.empty()) {
        std::cout << "\n--- Metal Items ---\n";
        for (const auto& item : metalItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!hazardousItems.empty()) {
        std::cout << "\n--- Hazardous Waste Items ---\n";
        for (const auto& item : hazardousItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!electronicItems.empty()) {
        std::cout << "\n--- Electronic Waste Items ---\n";
        for (const auto& item : electronicItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!paperItems.empty()) {
        std::cout << "\n--- Paper Items ---\n";
        for (const auto& item : paperItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!organicItems.empty()) {
        std::cout << "\n--- Organic Waste Items ---\n";
        for (const auto& item : organicItems) {
            std::cout << "- " << item << "\n";
        }
    }

    if (!generalItems.empty()) {
        std::cout << "\n--- General Waste Items ---\n";
        for (const auto& item : generalItems) {
            std::cout << "- " << item << "\n";
        }
    }

    // Simulate processing each category
    std::cout << "\n--- Processing Waste Categories ---\n";

    // Process each waste category


    if (!plasticItems.empty()) {
        std::cout << "\nProcessing Plastic Waste...\n";
        for (const auto& item : plasticItems) {
            std::cout << "Sending " << item << " to plastic recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
             // Simulate time for processing
        }
    }

    if (!glassItems.empty()) {
        std::cout << "\nProcessing Glass Waste...\n";
        for (const auto& item : glassItems) {
            std::cout << "Sending " << item << " to glass recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            // Simulate time for processing
        }
    }

    if (!metalItems.empty()) {
        std::cout << "\nProcessing Metal Waste...\n";
        for (const auto& item : metalItems) {
            std::cout << "Sending " << item << " to metal recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
             // Simulate time for processing
        }
    }

    if (!hazardousItems.empty()) {
        std::cout << "\nProcessing Hazardous Waste...\n";
        for (const auto& item : hazardousItems) {
            std::cout << "Sending " << item << " to hazardous waste disposal facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            // Simulate time for processing
        }
    }

    if (!electronicItems.empty()) {
        std::cout << "\nProcessing Electronic Waste...\n";
        for (const auto& item : electronicItems) {
            std::cout << "Sending " << item << " to electronic waste facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
             // Simulate time for processing
        }
    }

    if (!paperItems.empty()) {
        std::cout << "\nProcessing Paper Waste...\n";
        for (const auto& item : paperItems) {
            std::cout << "Sending " << item << " to paper recycling facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            // Simulate time for processing
        }
    }

    if (!organicItems.empty()) {
        std::cout << "\nProcessing Organic Waste...\n";
        for (const auto& item : organicItems) {
            std::cout << "Sending " << item << " to composting facility.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
             // Simulate time for processing
        }
    }

    if (!generalItems.empty()) {
        std::cout << "\nProcessing General Waste...\n";
        for (const auto& item : generalItems) {
            std::cout << "Sending " << item << " to general landfill.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            // Simulate time for processing
        }
    }

    // Final summary of all classifications and processing
    std::cout << "\nWaste Classification and Processing completed successfully.\n";
}


//time req for decompsition

// Function to simulate a complex task (e.g., waste processing)
void processWasteItems() {
    std::cout << "[Task] Starting waste item processing...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    // Simulate processing time for waste
    std::cout << "[Task] Waste items processed successfully.\n";
}

// Function to simulate data cleanup task
void performDataCleanup() {
    std::cout << "[Task] Cleaning up data...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
     // Simulate time for cleanup
    std::cout << "[Task] Data cleanup completed.\n";
}

// Function to simulate waste sorting task
void performWasteSorting() {
    std::cout << "[Task] Sorting recyclable and non-recyclable waste...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    // Simulate time for sorting waste
    std::cout << "[Task] Waste sorting completed.\n";
}

// Function to simulate a task that requires heavy computation
void heavyComputationTask() {
    std::cout << "[Task] Performing heavy computation...\n";
    long long result = 0;
    for (long long i = 0; i < 100000000; ++i) {
        result += i;  // Simulate a heavy computation task
    }
    std::cout << "[Task] Computation completed, result: " << result << "\n";
}

// Function to calculate the time taken by a process
void calculateProcessTime(const std::string& phaseName, std::function<void()> phaseFunction) {
    std::cout << "\nStarting Phase: " << phaseName << "...\n";
    std::string timestampBefore = getCurrentTime();
    std::cout << "Timestamp before " << phaseName << ": " << timestampBefore << "\n";

    std::clock_t start = std::clock();

    phaseFunction();
     // Execute the passed function (e.g., sorting, processing)

    std::clock_t end = std::clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;

    std::string timestampAfter = getCurrentTime();
    std::cout << "Timestamp after " << phaseName << ": " << timestampAfter << "\n";
    std::cout << "Time taken for " << phaseName << ": " << duration << " seconds.\n";

    // Simulate a status report for the phase
    std::cout << "Phase " << phaseName << " completed. Analyzing performance...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    // Simulate analysis delay
    std::cout << "Phase " << phaseName << " performance report generated.\n";

    // Simulate additional actions (logging or cleanup)
    std::cout << "[Task] Performing additional actions for " << phaseName << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    // Simulate some extra task
    std::cout << "[Task] Additional actions completed for " << phaseName << ".\n";

    // Provide a final summary of the phase
    std::cout << "\n--- Final Summary for " << phaseName << " ---\n";
    std::cout << "Phase " << phaseName << " has been executed successfully.\n";
    std::cout << "Total time taken: " << duration << " seconds.\n";
    std::cout << "Phase " << phaseName << " completed at: " << timestampAfter << "\n";

    // Optional: Add some recommendations or feedback
    if (duration > 1.0) {
        std::cout << "Recommendation: Phase " << phaseName << " might need optimization.\n";
    } else {
        std::cout << "Phase " << phaseName << " executed efficiently.\n";
    }

    std::cout << "Process summary generated at: " << getCurrentTime() << "\n";
    std::cout << "Report for " << phaseName << " completed.\n";
}

// Function to simulate a multi-step process, calculating times for each step
void multiStepProcess() {
    std::cout << "\nStarting multi-step process...\n";

    calculateProcessTime("Sorting Items", performWasteSorting);
    calculateProcessTime("Processing Waste", processWasteItems);
    calculateProcessTime("Data Cleanup", performDataCleanup);
    calculateProcessTime("Waste Sorting", performWasteSorting);
    calculateProcessTime("Heavy Computation", heavyComputationTask);

    std::cout << "\nMulti-step process completed.\n";
}

// Main simulation function

void manageWasteProcess() {
    // Hardcoded waste items
    std::vector<std::string> sqlData = {
        "Plastic Bottle", "Glass Jar", "Metal Can", "Paper Bag",
        "Food Waste", "Plant Leaves", "Inorganic Chemical",
        "Plastic Wrapper", "Old Newspaper", "Broken Toy",
        "Banana Peel", "Organic Compost", "Used Batteries",
        "Plastic Straw", "Old Computer", "TV Screen", "E-Waste",
        "Hazardous Chemical", "Used Electronics"
    }; // Example data

    // Classification of waste items
    std::map<std::string, std::string> classifications;
    for (const auto& waste : sqlData) {
        classifications[waste] = "Recyclable";
         // Example classification
    }

    int phase;
    do {
        std::cout << "\nSelect Phase (0 to exit):\n";
        std::cout << "1. Displaying the Classification\n";
        std::cout << "2. Preliminary Inspection\n";
        std::cout << "3. Manual Sorting\n";
        std::cout << "4. Mechanical Sorting\n";
       // std::cout << "5. Advanced Sorting\n";
        //std::cout << "6. Handle Additional Categories\n";

        std::cout << "5. Send Recyclable Items to Factory\n";
        std::cout << "6. Send Sellable Items to Market\n";
        std::cout << "7. Send Burnable Items to Incinerator\n";
        std::cout << "8. Send Hazardous Waste to Destruction\n";
        std::cout << "9. Send to factory\n";
        std::cout << "10. Display biodegradable items\n";
        std::cout << "Enter choice: ";
        std::cin >> phase;

        switch (phase) {
        case 1:
            std::cout << "\nDisplaying the Classification:\n";
            for (const auto& item : classifications) {
                std::cout << item.first << " is classified as " << item.second << std::endl;
            }
            std::cout << "\nDisplaying waste items:\n";
            for (const auto& waste : sqlData) {
                std::cout << "Waste Item: " << waste << std::endl;
            }
               displayWasteItems(sqlData);
            break;

        case 2:
            std::cout << "\nPreliminary Inspection started...\n";
            // Insert logic for preliminary inspection here

              preliminaryInspection(sqlData);
            std::cout << "Preliminary Inspection finished.\n";

            break;

        case 3:
            std::cout << "\nManual Sorting started...\n";
            // Insert logic for manual sorting here

              manualSorting(sqlData);
            std::cout << "Manual Sorting finished.\n";

            break;

        case 4:
            std::cout << "\nMechanical Sorting started...\n";
            // Insert logic for mechanical sorting here

              mechanicalSorting(sqlData);
            std::cout << "Mechanical Sorting finished.\n";
            break;

       // case 5:
          //  std::cout << "\nAdvanced Sorting started...\n";
            // Insert logic for advanced sorting here

            //   advancedSorting(sqlData);
//
  //          std::cout << "Advanced Sorting finished.\n";
    //        break;

      //  case 6:
        //    std::cout << "\nHandling Additional Categories...\n";
            // Insert logic for additional categories here

          //      handleAdditionalCategories(classifications);
            //std::cout << "Handling Additional Categories finished.\n";
            //break;

        case 5:
            std::cout << "\nSending Recyclable Items to Factory...\n";
            // Insert logic for sending recyclable items to factory here

              sendToFactory(classifications);
            std::cout << "Recyclable Items sent to Factory.\n";
            break;

        case 6:
            std::cout << "\nSending Sellable Items to Market...\n";
            // Insert logic for sending sellable items to market here
               sendToSell(classifications);
            std::cout << "Sellable Items sent to Market.\n";
            break;

        case 7:
            std::cout << "\nSending Burnable Items to Incinerator...\n";
            // Insert logic for sending burnable items to incinerator here

              sendToBurn(classifications);
            std::cout << "Burnable Items sent to Incinerator.\n";


            break;

        case 8:
            std::cout << "\nSending Hazardous Waste to Destruction...\n";
            // Insert logic for sending hazardous waste to destruction here

                 sendToDestroy(classifications);
            std::cout << "Hazardous Waste sent to Destruction.\n";
            break;

        case 9:
            std::cout << "\nSending recyclable waste to factory...\n";
            // Insert logic for recyclable waste to factory here
            sendToFactory(classifications);
            std::cout << "Recyclable waste to factory.\n";
            break;

        case 10:
            std::cout << "\nBiodegradable waste items are...\n";
            // Insert logic for biodegradable waste items here

             displayBiodegradableItems(sqlData);
            std::cout << "Biodegradable waste items.\n";
            break;

        default:
     if (phase != 0) {
                std::cout << "Invalid choice. Please try again.\n";
            }
            break;
        }

    } while (phase != 0);  // Exit loop whenÂ phaseÂ isÂ 0
}

//module 4

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
#include <limits>
#include <sstream>

using namespace std;

// Utility functions for logging and formatting
void logTransaction(const string& message)
{
    // Logs messages with timestamps to the console for tracking
    time_t now = time(0);
    cout << "LOG [" << ctime(&now) << "]: " << message << endl;
}

string getCurrentTimestamp()
{
    // Returns the current timestamp as a string
    time_t now = time(0);
    return ctime(&now);
}

// User class to handle authentication and roles
class User
{
private:
    string username;
    string password;
    string role;

public:
    User(string username, string password, string role)
        : username(username), password(password), role(role)
        {}

    string getUsername() const
    {
        return username;
    }
    string getRole() const
    {
        return role;
    }

    // Method to authenticate a user based on the entered password
    bool authenticate(const string& enteredPassword) const
    {
        return enteredPassword == password;
    }

    // Static method to load predefined users into the system
    static vector<User> loadUsers()
    {
        return
        {
            User("admin", "admin123", "Admin"),
            User("user", "user123", "User")
        };
    }
};

// Product class to manage products in the system
class Product
{
private:
    string name;
    string category;
    double price;
    int quantity;

public:
    Product(string name, string category, double price, int quantity)
        : name(name), category(category), price(price), quantity(quantity) {}

    // Getters for product attributes
    string getName() const
    {
        return name;
    }
    string getCategory() const
    {
        return category;
    }
    double getPrice() const
    {
        return price;
    }
    int getQuantity() const
    {
        return quantity;
    }

    // Method to add stock to the product
    void addStock(int qty)
    {
        quantity += qty;
    }

    // Method to update product details
    void updateProduct(const string& newName, const string& newCategory, double newPrice, int newQuantity)
    {
        name = newName;
        category = newCategory;
        price = newPrice;
        quantity = newQuantity;
    }

    // Method to reduce stock by selling a specified quantity
    bool sell(int qty, double discountRate, double& totalCost, double& discountApplied)
    {
        if (qty > quantity)
        {
            cout << "Insufficient stock for " << name << ". Available: " << quantity << endl;
            return false;
        }

        // Calculate total cost and apply discount for bulk purchases
        totalCost = price * qty;
        discountApplied = 0.0;

        if (qty > 20)
        {
            // Bulk order threshold
            discountApplied = totalCost * discountRate;
            totalCost -= discountApplied;
        }

        quantity -= qty;

        // Reduce the quantity after the sale
        return true;
    }

    // Display product details in a formatted table
    void displayProduct() const
    {
        cout << setw(20) << left << name
             << setw(15) << category
             << setw(10) << right << price
             << setw(10) << right << quantity << endl;
    }
};

// WasteManagementSystem class manages inventory and transactions
class WasteManagementSystem
{
private:
    vector<Product> products;
    // List of products
    const double bulkDiscountRate = 0.1;
    // 10% discount for bulk orders

    // Find the index of a product by name
    int findProduct(const string& name) const
    {
        for (size_t i = 0; i < products.size(); ++i)
        {
            if (products[i].getName() == name) return i;
        }
        return -1;
        // Return -1 if the product is not found
    }

    // Function to display inventory statistics
    void displayStatistics() const
    {
        double totalValue = 0.0;
        int totalProducts = 0;
        for (const auto& product : products)
        {
            totalValue += product.getPrice() * product.getQuantity();
            totalProducts += product.getQuantity();
        }
        cout << "\n--- Inventory Statistics ---\n";
        cout << "Total Inventory Value: â‚¹" << fixed << setprecision(2) << totalValue << endl;
        cout << "Total Products in Stock: " << totalProducts << endl;
        cout << "Number of Product Types: " << products.size() << endl;
    }

public:
    WasteManagementSystem()
    {
        // Predefined products for testing
        products = {
            {"Glass Bottles", "Recyclable", 10.0, 50},
            {"Plastic Bottles", "Recyclable", 5.0, 100},
            {"Metal Cans", "Recyclable", 15.0, 75},
            {"Cardboard", "Recyclable", 2.0, 200},
            {"Electronics", "E-waste", 500.0, 10},
            {"Paper", "Recyclable", 1.0, 300},
            {"Batteries", "Hazardous", 50.0, 20},
            {"Clothing", "Recyclable", 100.0, 25},
            {"Furniture", "Bulky Waste", 2000.0, 5},
            {"Tires", "Non-Recyclable", 300.0, 30}
        };
    }

    // Add or update a product in the inventory
    void addProduct(const string& name, const string& category, double price, int quantity)
    {
        int index = findProduct(name);
        if (index != -1)
        {
            products[index].addStock(quantity);
            // Update stock if product exists
        } else
        {
            products.emplace_back(name, category, price, quantity);
            // Add a new product
        }
        cout << "Added/Updated product: " << name << " with quantity: " << quantity << endl;
        logTransaction("Added/Updated product: " + name);
    }

    // Update an existing product's details
    void updateProduct(const string& name, const string& newName, const string& newCategory, double newPrice, int newQuantity)
    {
        int index = findProduct(name);
        if (index == -1)
        {
            cout << "Product not found: " << name << endl;
            return;
        }

        products[index].updateProduct(newName, newCategory, newPrice, newQuantity);
        cout << "Updated product details for: " << name << endl;
        logTransaction("Updated product details for: " + name);
    }

    // Display all available products
    void viewProducts() const
    {
        if (products.empty())
        {
            cout << "No products available." << endl;
            return;
        }

        cout << setw(20) << left << "Product Name"
             << setw(15) << "Category"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << endl;
        cout << string(55, '-')
        << endl;

        for (const auto& product : products)
        {
            product.displayProduct();
        }
    }

    // Sell a product by name and quantity
    void sellProduct(const string& name, int quantity)
    {
        int index = findProduct(name);
        if (index == -1)
        {
            cout << "Product not found: " << name << endl;
            return;
        }

        double totalCost = 0.0, discountApplied = 0.0;

        if (products[index].sell(quantity, bulkDiscountRate, totalCost, discountApplied))
        {
            cout << "Sold " << quantity << " units of " << name << endl;
            cout << fixed << setprecision(2);
            if (discountApplied > 0)
            {
                cout << "Bulk discount applied: â‚¹" << discountApplied << endl;
            }
            cout << "Total cost: â‚¹" << totalCost << endl;

            string logMsg = "Sold " + to_string(quantity) + " units of " + name +
                            " (Discount: â‚¹" + to_string(discountApplied) + ")";
            logTransaction(logMsg);
        }
    }

    // Advanced product search
    void searchProduct(const string& keyword) const
    {
        bool found = false;
        cout << "Searching for products with keyword: " << keyword << endl;
        for (const auto& product : products)
        {
            if (product.getName().find(keyword) != string::npos ||
                product.getCategory().find(keyword) != string::npos)
            {
                product.displayProduct();
                found = true;
            }
        }
        if (!found)
        {
            cout << "No products matched your search." << endl;
        }
    }

    // Display inventory report with statistics
    void generateReport() const
    {
        cout << "\n--- Inventory Report ---" << endl;
        if (products.empty())
        {
            cout << "No products available for report generation." << endl;
            return;
        }

        cout << setw(20) << left << "Product Name"
             << setw(15) << "Category"
             << setw(10) << "Price"
             << setw(10) << "Quantity" << endl;
        cout << string(55, '-') << endl;

        for (const auto& product : products)
        {
            product.displayProduct();
        }

        // Display statistics at the end of the report
        displayStatistics();
        cout << "------------------------- End of Report -------------------------\n" << endl;
    }
};

// Display the main menu for the system
void displayMenu()
{
    cout << "\n--- Waste Management System ---\n";
    cout << "1. Add Recycled Product\n";
    cout << "2. View Products\n";
    cout << "3. Sell Product\n";
    cout << "4. Generate Report\n";
    cout << "5. Search Product\n";
    cout << "6. Update Product Details\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

// Clear the input buffer to handle invalid inputs
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int manageWasteSystem() {
    vector<User> users = User::loadUsers();
    // Load predefined users
    string username, password;

    // User authentication
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    User* loggedInUser = nullptr;
    // Pointer to store the logged-in user
    for (const auto& user : users)
    {
        if (user.getUsername() == username && user.authenticate(password))
        {
            loggedInUser = new User(user);
            break;
        }
    }

    if (!loggedInUser)
    {
        cout << "Invalid credentials. Exiting program." << endl;
        return 1;
    }

    cout << "Welcome, " << loggedInUser->getUsername() << " (" << loggedInUser->getRole() << ")!" << endl;

    WasteManagementSystem system;
    // Instantiate the WasteManagementSystem

    while (true)
    {
        displayMenu();
        // Display the menu
        int choice;
        cin >> choice;

        if (cin.fail())
        {
            clearInputBuffer();
            cout << "Invalid input. Please enter a valid choice." << endl;
            continue;
        }

        try
        {
            if (choice == 1)
            {
                string name, category;
                double price;
                int quantity;

                cout << "Enter product name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter price per unit: ";
                cin >> price;
                cout << "Enter quantity: ";
                cin >> quantity;

                system.addProduct(name, category, price, quantity);
            }
            else if (choice == 2)
            {
                system.viewProducts();
            }
            else if (choice == 3)
            {
                string name;
                int quantity;

                cout << "Enter product name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter quantity to sell: ";
                cin >> quantity;

                system.sellProduct(name, quantity);
            }
            else if (choice == 4)
            {
                system.generateReport();
            }
            else if (choice == 5)
            {
                string keyword;
                cout << "Enter keyword to search: ";
                cin.ignore();
                getline(cin, keyword);

                system.searchProduct(keyword);
            }
            else if (choice == 6)
            {
                string name, newName, newCategory;
                double newPrice;
                int newQuantity;

                cout << "Enter current product name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new product name: ";
                getline(cin, newName);
                cout << "Enter new category: ";
                getline(cin, newCategory);
                cout << "Enter new price per unit: ";
                cin >> newPrice;
                cout << "Enter new quantity: ";
                cin >> newQuantity;

                system.updateProduct(name, newName, newCategory, newPrice, newQuantity);
            }
            else if (choice == 7)
            {
                cout << "Exiting system. Goodbye!" << endl;
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
        }
    }

    delete loggedInUser;

    // Clean up the allocated user object
    return 0;
}
//Username- admin
//Password-admin123

//main

#include <iostream>
using namespace std;

int main() {
    int choice;
    Graph g;  // Declare the variable outside the switch


     cout << "\n";
    cout << "*****************************************************\n";
    cout << "*                                                   *\n";
    cout << "*           Welcome to the Waste Management         *\n";
    cout << "*                  System!                          *\n";
    cout << "*                                                   *\n";
    cout << "*****************************************************\n";


    do {
        // Display the menu for the user to choose an operation
        cout << "\nSelect an option:\n";
        cout << "1. Waste genration\n";
        cout << "2. Route optimization\n";
        cout << "3. Waste classification\n";
        cout << "4. Waste valuation\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Call function to manage waste areas
                cout<<"\n\n***********  Waste genration ***************\n\n";
                manageWasteAreas(g);  // Assuming this function manages the waste areas
                break;

            case 2:
                // Call function to manage waste collection and traffic
                  cout<<"\n\n***********  Route optimization ***************\n\n";
            simulateWasteManagement();
                break;

            case 3:
                // Call function to manage waste process
                cout<<"\n\n*********** Waste classification ***************\n\n";

                manageWasteProcess();  // Assuming this function handles waste processing

                break;

            case 4:
                // Call function to manage waste system
                cout<<"\n\n***********Waste valuation***************\n\n";
                manageWasteSystem();  // Assuming this function manages the waste system
                break;

            case 5:

                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 5);  // Continue until the user chooses to exit

    return 0;
}
#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <numeric>
#include <sstream>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <set>
#include <functional>
using namespace std;

// Define a struct for recycled products
struct RecycledProduct {
    string wasteType;
    string productName;
    double price;
};

// Define a struct for the user cart
struct CartItem {
    RecycledProduct product;
    int quantity;
};

// Define a graph for waste-product relationships
class ProductGraph {
private:
    unordered_map<string, vector<string>> adjList;

public:
    void addEdge(const string& wasteType, const string& productName) {
        adjList[wasteType].push_back(productName);
    }

    void displayGraph() const {
        cout << "\nWaste-Product Relationships:" << endl;
        for (const auto& pair : adjList) {
            cout << pair.first << " -> ";
            for (const auto& product : pair.second) {
                cout << product << ", ";
            }
            cout << endl;
        }
    }

    vector<string> getRelatedProducts(const string& wasteType) const {
        auto it = adjList.find(wasteType);
        if (it != adjList.end()) {
            return it->second;
        }
        return {};
    }

    void bfsTraversal(const string& start) const {
        if (adjList.find(start) == adjList.end()) {
            cout << "\nNo products found for this waste type." << endl;
            return;
        }

        cout << "\nBFS Traversal from " << start << ":\n";
        queue<string> q;
        set<string> visited;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();

            cout << current << " -> ";

            for (const auto& neighbor : adjList.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        cout << "END" << endl;
    }

    void dfsTraversal(const string& start) const {
        unordered_map<string, bool> visited;

        function<void(const string&)> dfs = [&](const string& node) {
            visited[node] = true;
            cout << node << " -> ";
            for (const auto& neighbor : getRelatedProducts(node)) {
                if (!visited[neighbor]) {
                    dfs(neighbor);
                }
            }
        };

        if (getRelatedProducts(start).empty()) {
            cout << "\nNo related products found for the specified waste type." << endl;
        } else {
            cout << "\nDFS Traversal from " << start << ":\n";
            dfs(start);
            cout << "END" << endl;
        }
    }
};

// Function prototypes

void loadFromFile(const string& daa);
void selectCompany();
void displayProducts(const vector<RecycledProduct>& products);
void selectProduct(vector<RecycledProduct>& products, vector<CartItem>& cart);
void displayCart(const vector<CartItem>& cart);
void checkout(const vector<CartItem>& cart);
void loadProducts(vector<RecycledProduct>& products);
void saveCart(const vector<CartItem>& cart);
void loadCart(vector<CartItem>& cart, const vector<RecycledProduct>& products);
void setupGraph(ProductGraph& graph, const vector<RecycledProduct>& products);
bool isValidWasteType(const string& wasteType, const vector<RecycledProduct>& products);
void suggestWasteType(const vector<RecycledProduct>& products);
bool isConnected(const ProductGraph& graph, const string& waste1, const string& waste2);


void loadFromFile(const string& daa) {
    ifstream file(daa);
    if (!file.is_open())
        {

        cerr << "Failed to open the file: " << daa << endl;
        return;
    }

    string line;
    cout << "\nContents of the file " << daa << ":\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}




void displayProducts(const vector<RecycledProduct>& products) {
    if (products.empty()) {
        cout << "\nNo products available to display." << endl;
        return;
    }

    vector<RecycledProduct> filteredProducts = products;
    int filterChoice, sortChoice;
    string filterValue;

    // Step 1: Filter Options
    cout << "\nFilter Options:\n";
    cout << "1. Show All Products (No Filter)\n";
    cout << "2. Filter by Waste Type\n";
    cout << "3. Filter by Product Name Keyword\n";
    cout << "4. Filter by Price Range\n";
    cout << "Enter your filter choice: ";
    cin >> filterChoice;

    // Apply Filtering
    switch (filterChoice) {
        case 2: {
            cout << "\nEnter Waste Type to filter: ";
            cin >> filterValue;
            filteredProducts.erase(remove_if(filteredProducts.begin(), filteredProducts.end(),
                                             [&](const RecycledProduct& p) { return p.wasteType != filterValue; }),
                                   filteredProducts.end());
            break;
        }
        case 3: {
            cout << "\nEnter Product Name Keyword to filter: ";
            cin.ignore(); // Clear buffer
            getline(cin, filterValue);
            filteredProducts.erase(remove_if(filteredProducts.begin(), filteredProducts.end(),
                                             [&](const RecycledProduct& p) {
                                                 return p.productName.find(filterValue) == string::npos;
                                             }),
                                   filteredProducts.end());
            break;
        }
        case 4: {
            double minPrice, maxPrice;
            cout << "\nEnter minimum price: ";
            cin >> minPrice;
            cout << "Enter maximum price: ";
            cin >> maxPrice;
            filteredProducts.erase(remove_if(filteredProducts.begin(), filteredProducts.end(),
                                             [&](const RecycledProduct& p) {
                                                 return p.price < minPrice || p.price > maxPrice;
                                             }),
                                   filteredProducts.end());
            break;
        }
        case 1:
        default:
            break; // No filtering
    }

    if (filteredProducts.empty()) {
        cout << "\nNo products match the selected filter criteria." << endl;
        return;
    }

    // Step 2: Sort Options
    cout << "\nSort Options:\n";
    cout << "1. Sort by Waste Type (A-Z)\n";
    cout << "2. Sort by Product Name (A-Z)\n";
    cout << "3. Sort by Price (Low to High)\n";
    cout << "4. Sort by Price (High to Low)\n";
    cout << "Enter your sorting choice: ";
    cin >> sortChoice;

    // Apply Sorting
    switch (sortChoice) {
        case 1:
            sort(filteredProducts.begin(), filteredProducts.end(),
                 [](const RecycledProduct& a, const RecycledProduct& b) { return a.wasteType < b.wasteType; });
            break;
        case 2:
            sort(filteredProducts.begin(), filteredProducts.end(),
                 [](const RecycledProduct& a, const RecycledProduct& b) { return a.productName < b.productName; });
            break;
        case 3:
            sort(filteredProducts.begin(), filteredProducts.end(),
                 [](const RecycledProduct& a, const RecycledProduct& b) { return a.price < b.price; });
            break;
        case 4:
            sort(filteredProducts.begin(), filteredProducts.end(),
                 [](const RecycledProduct& a, const RecycledProduct& b) { return a.price > b.price; });
            break;
        default:
            cout << "\nInvalid sorting choice. Displaying products without sorting." << endl;
            break;
    }

    // Step 3: Display Products
    cout << "\nFiltered and Sorted Recycled Products:\n";
    cout << left << setw(5) << "No." << setw(20) << "Waste Type" << setw(25) << "Product Name" << "Price (in Rupees)" << endl;
    cout << string(60, '-') << endl;

    for (size_t i = 0; i < filteredProducts.size(); ++i) {
        cout << left << setw(5) << i + 1 << setw(20) << filteredProducts[i].wasteType
             << setw(25) << filteredProducts[i].productName << filteredProducts[i].price << endl;
    }

    // Step 4: Export Options
    char exportChoice;
    cout << "\nWould you like to export the displayed products to a file? (y/n): ";
    cin >> exportChoice;

    if (exportChoice == 'y' || exportChoice == 'Y') {
        ofstream file("filtered_products.txt");
        if (!file) {
            cerr << "\nFailed to create the file." << endl;
            return;
        }

        file << left << setw(5) << "No." << setw(20) << "Waste Type" << setw(25) << "Product Name" << "Price (in Rupees)" << endl;
        file << string(60, '-') << endl;
        for (size_t i = 0; i < filteredProducts.size(); ++i) {
            file << left << setw(5) << i + 1 << setw(20) << filteredProducts[i].wasteType
                 << setw(25) << filteredProducts[i].productName << filteredProducts[i].price << endl;
        }

        cout << "\nProducts successfully exported to 'filtered_products.txt'." << endl;
    }

    // Step 5: Additional Analysis
    cout << "\nAdditional Analysis Options:\n";
    cout << "1. Find the Most Expensive Product\n";
    cout << "2. Find the Cheapest Product\n";
    cout << "3. Calculate Average Product Price\n";
    cout << "Enter your choice (or 0 to skip): ";
    int analysisChoice;
    cin >> analysisChoice;

    switch (analysisChoice) {
        case 1: {
            auto maxProduct = max_element(filteredProducts.begin(), filteredProducts.end(),
                                          [](const RecycledProduct& a, const RecycledProduct& b) { return a.price < b.price; });
            cout << "\nMost Expensive Product:\n";
            cout << "Waste Type: " << maxProduct->wasteType << "\nProduct Name: " << maxProduct->productName
                 << "\nPrice: " << maxProduct->price << " Rupees" << endl;
            break;
        }
        case 2: {
            auto minProduct = min_element(filteredProducts.begin(), filteredProducts.end(),
                                          [](const RecycledProduct& a, const RecycledProduct& b) { return a.price < b.price; });
            cout << "\nCheapest Product:\n";
            cout << "Waste Type: " << minProduct->wasteType << "\nProduct Name: " << minProduct->productName
                 << "\nPrice: " << minProduct->price << " Rupees" << endl;
            break;
        }
        case 3: {
            double totalPrice = accumulate(filteredProducts.begin(), filteredProducts.end(), 0.0,
                                           [](double sum, const RecycledProduct& p) { return sum + p.price; });
            double averagePrice = totalPrice / filteredProducts.size();
            cout << "\nAverage Product Price: " << averagePrice << " Rupees" << endl;
            break;
        }
        case 0:
        default:
            cout << "\nSkipping additional analysis." << endl;
            break;
    }
}



// Function to handle product selection and add to cart
void selectProduct(vector<RecycledProduct>& products, vector<CartItem>& cart) {
    if (products.empty()) {
        cout << "\nNo products available for selection." << endl;
        return;
    }

    int choice;
    string searchKeyword;
    char action;
    bool productSelected = false;

    while (!productSelected) {
        cout << "\nProduct Selection Menu:" << endl;
        cout << "1. Search for a product by keyword" << endl;
        cout << "2. View all products and select" << endl;
        cout << "3. Exit selection" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore(); // Clear buffer
                cout << "\nEnter a keyword to search for a product: ";
                getline(cin, searchKeyword);

                vector<int> matchingIndexes;
                for (size_t i = 0; i < products.size(); ++i) {
                    if (products[i].productName.find(searchKeyword) != string::npos ||
                        products[i].wasteType.find(searchKeyword) != string::npos) {
                        matchingIndexes.push_back(i);
                    }
                }

                if (matchingIndexes.empty()) {
                    cout << "\nNo products found matching the keyword \"" << searchKeyword << "\"." << endl;
                } else {
                    cout << "\nMatching Products:" << endl;
                    cout << left << setw(5) << "No." << setw(20) << "Waste Type" << setw(25) << "Product Name" << "Price (in Rupees)" << endl;
                    cout << string(60, '-') << endl;
                    for (size_t i = 0; i < matchingIndexes.size(); ++i) {
                        const auto& product = products[matchingIndexes[i]];
                        cout << left << setw(5) << i + 1 << setw(20) << product.wasteType
                             << setw(25) << product.productName << product.price << endl;
                    }

                    cout << "\nEnter the number corresponding to the product to select it, or 0 to cancel: ";
                    int selectedIndex;
                    cin >> selectedIndex;

                    if (selectedIndex > 0 && selectedIndex <= static_cast<int>(matchingIndexes.size())) {
                        const RecycledProduct& selectedProduct = products[matchingIndexes[selectedIndex - 1]];
                        int quantity;
                        cout << "\nSelected Product Details:" << endl;
                        cout << "Waste Type: " << selectedProduct.wasteType << endl;
                        cout << "Product Name: " << selectedProduct.productName << endl;
                        cout << "Price: " << selectedProduct.price << " Rupees" << endl;
                        cout << "Enter quantity to add to cart: ";
                        cin >> quantity;

                        if (quantity > 0) {
                            cart.push_back({selectedProduct, quantity});
                            cout << "\nAdded " << quantity << " x " << selectedProduct.productName << " to your cart." << endl;
                            productSelected = true;
                        } else {
                            cout << "\nInvalid quantity. Please try again." << endl;
                        }
                    } else if (selectedIndex == 0) {
                        cout << "\nProduct selection cancelled." << endl;
                    } else {
                        cout << "\nInvalid choice. Please try again." << endl;
                    }
                }
                break;
            }

            case 2: {
                cout << "\nAvailable Products:" << endl;
                cout << left << setw(5) << "No." << setw(20) << "Waste Type" << setw(25) << "Product Name" << "Price (in Rupees)" << endl;
                cout << string(60, '-') << endl;
                for (size_t i = 0; i < products.size(); ++i) {
                    cout << left << setw(5) << i + 1 << setw(20) << products[i].wasteType
                         << setw(25) << products[i].productName << products[i].price << endl;
                }

                cout << "\nEnter the number corresponding to the product you want to select: ";
                int selectedIndex;
                cin >> selectedIndex;

                if (selectedIndex > 0 && selectedIndex <= static_cast<int>(products.size())) {
                    const RecycledProduct& selectedProduct = products[selectedIndex - 1];
                    int quantity;
                    cout << "\nSelected Product Details:" << endl;
                    cout << "Waste Type: " << selectedProduct.wasteType << endl;
                    cout << "Product Name: " << selectedProduct.productName << endl;
                    cout << "Price: " << selectedProduct.price << " Rupees" << endl;
                    cout << "Enter quantity to add to cart: ";
                    cin >> quantity;

                    if (quantity > 0) {
                        cart.push_back({selectedProduct, quantity});
                        cout << "\nAdded " << quantity << " x " << selectedProduct.productName << " to your cart." << endl;
                        productSelected = true;
                    } else {
                        cout << "\nInvalid quantity. Please try again." << endl;
                    }
                } else {
                    cout << "\nInvalid choice. Please try again." << endl;
                }
                break;
            }

            case 3:
                cout << "\nExiting product selection menu." << endl;
                return;

            default:
                cout << "\nInvalid choice. Please try again." << endl;
                break;
        }
    }
}

// Function to display the cart contents
void displayCart(const vector<CartItem>& cart) {
    if (cart.empty()) {
        cout << "\nYour cart is empty." << endl;
        return;
    }

    cout << "\nYour Cart:\n";
    cout << left << setw(5) << "No." << setw(25) << "Product Name" << setw(15) << "Waste Type"
         << setw(10) << "Quantity" << "Total Price (in Rupees)" << endl;
    cout << string(80, '-') << endl;

    double grandTotal = 0.0;
    unordered_map<string, double> categoryTotals; // To calculate total price per waste type
    unordered_map<string, int> categoryQuantities; // To calculate quantity per waste type

    for (size_t i = 0; i < cart.size(); ++i) {
        double total = cart[i].quantity * cart[i].product.price;
        grandTotal += total;
        categoryTotals[cart[i].product.wasteType] += total;
        categoryQuantities[cart[i].product.wasteType] += cart[i].quantity;

        cout << left << setw(5) << i + 1 << setw(25) << cart[i].product.productName
             << setw(15) << cart[i].product.wasteType << setw(10) << cart[i].quantity << total << endl;
    }

    cout << "\nGrand Total: " << grandTotal << " Rupees" << endl;

    // Display category-wise breakdown
    cout << "\nCategory-Wise Breakdown:\n";
    cout << left << setw(20) << "Waste Type" << setw(15) << "Total Quantity"
         << "Total Price (in Rupees)" << endl;
    cout << string(60, '-') << endl;
    for (const auto& [wasteType, totalPrice] : categoryTotals) {
        cout << left << setw(20) << wasteType << setw(15) << categoryQuantities[wasteType] << totalPrice << endl;
    }

    // Additional analysis
    cout << "\nAdditional Analysis Options:\n";
    cout << "1. Most Purchased Product\n";
    cout << "2. Most Expensive Product in Cart\n";
    cout << "3. Cheapest Product in Cart\n";
    cout << "4. Average Price of Items in Cart\n";
    cout << "5. Export Cart Details to File\n";
    cout << "Enter your choice (or 0 to skip): ";
    int analysisChoice;
    cin >> analysisChoice;

    switch (analysisChoice) {
        case 1: {
            auto maxItem = max_element(cart.begin(), cart.end(),
                                       [](const CartItem& a, const CartItem& b) {
                                           return a.quantity < b.quantity;
                                       });
            cout << "\nMost Purchased Product:\n";
            cout << "Product Name: " << maxItem->product.productName << "\nWaste Type: "
                 << maxItem->product.wasteType << "\nQuantity: " << maxItem->quantity << endl;
            break;
        }
        case 2: {
            auto maxPriceItem = max_element(cart.begin(), cart.end(),
                                            [](const CartItem& a, const CartItem& b) {
                                                return (a.quantity * a.product.price) <
                                                       (b.quantity * b.product.price);
                                            });
            cout << "\nMost Expensive Product in Cart:\n";
            cout << "Product Name: " << maxPriceItem->product.productName << "\nWaste Type: "
                 << maxPriceItem->product.wasteType << "\nTotal Price: "
                 << (maxPriceItem->quantity * maxPriceItem->product.price) << " Rupees" << endl;
            break;
        }
        case 3: {
            auto minPriceItem = min_element(cart.begin(), cart.end(),
                                            [](const CartItem& a, const CartItem& b) {
                                                return (a.quantity * a.product.price) <
                                                       (b.quantity * b.product.price);
                                            });
            cout << "\nCheapest Product in Cart:\n";
            cout << "Product Name: " << minPriceItem->product.productName << "\nWaste Type: "
                 << minPriceItem->product.wasteType << "\nTotal Price: "
                 << (minPriceItem->quantity * minPriceItem->product.price) << " Rupees" << endl;
            break;
        }
        case 4: {
            double totalItems = 0;
            for (const auto& item : cart) {
                totalItems += item.quantity;
            }
            double averagePrice = (totalItems > 0) ? grandTotal / totalItems : 0.0;
            cout << "\nAverage Price of Items in Cart: " << averagePrice << " Rupees" << endl;
            break;
        }
        case 5: {
            ofstream file("cart_details.txt");
            if (!file) {
                cerr << "\nFailed to export cart details." << endl;
                return;
            }

            file << left << setw(5) << "No." << setw(25) << "Product Name" << setw(15) << "Waste Type"
                 << setw(10) << "Quantity" << "Total Price (in Rupees)" << endl;
            file << string(80, '-') << endl;

            for (size_t i = 0; i < cart.size(); ++i) {
                double total = cart[i].quantity * cart[i].product.price;
                file << left << setw(5) << i + 1 << setw(25) << cart[i].product.productName
                     << setw(15) << cart[i].product.wasteType << setw(10) << cart[i].quantity << total << endl;
            }

            file << "\nGrand Total: " << grandTotal << " Rupees\n";

            file << "\nCategory-Wise Breakdown:\n";
            file << left << setw(20) << "Waste Type" << setw(15) << "Total Quantity"
                 << "Total Price (in Rupees)" << endl;
            file << string(60, '-') << endl;
            for (const auto& [wasteType, totalPrice] : categoryTotals) {
                file << left << setw(20) << wasteType << setw(15) << categoryQuantities[wasteType] << totalPrice
                     << endl;
            }

            cout << "\nCart details successfully exported to 'cart_details.txt'." << endl;
            break;
        }
        case 0:
        default:
            cout << "\nSkipping additional analysis." << endl;
            break;
    }
}


// Function to handle checkout process
// Function to handle the checkout process
void checkout(const vector<CartItem>& cart) {
    if (cart.empty()) {
        cout << "\nYour cart is empty. Nothing to checkout." << endl;
        return;
    }

    double grandTotal = 0.0;
    for (const auto& item : cart) {
        grandTotal += item.quantity * item.product.price;
    }

    // Apply discounts
    double discount = 0.0;
    if (grandTotal > 1000.0) {
        discount = grandTotal * 0.10; // 10% discount for purchases above 1000
        cout << "\nCongratulations! You received a 10% discount for spending over 1000.\n";
    }

    double finalTotal = grandTotal - discount;

    // Display detailed receipt
    cout << "\n--- Checkout Receipt ---\n";
    cout << left << setw(5) << "No." << setw(25) << "Product Name" << setw(10) << "Quantity"
         << setw(15) << "Unit Price" << "Total Price" << endl;
    cout << string(70, '-') << endl;

    for (size_t i = 0; i < cart.size(); ++i) {
        double total = cart[i].quantity * cart[i].product.price;
        cout << left << setw(5) << i + 1 << setw(25) << cart[i].product.productName
             << setw(10) << cart[i].quantity << setw(15) << cart[i].product.price << total << endl;
    }

    cout << "\nSubtotal: " << grandTotal << " Rupees";
    if (discount > 0.0) {
        cout << "\nDiscount: " << discount << " Rupees";
    }
    cout << "\nFinal Total: " << finalTotal << " Rupees\n";

    // Save receipt to a file
    char saveReceipt;
    cout << "\nWould you like to save the receipt to a file? (y/n): ";
    cin >> saveReceipt;

    if (saveReceipt == 'y' || saveReceipt == 'Y') {
        ofstream receiptFile("receipt.txt");
        if (!receiptFile) {
            cerr << "Failed to save the receipt." << endl;
        } else {
            receiptFile << "--- Checkout Receipt ---\n";
            receiptFile << left << setw(5) << "No." << setw(25) << "Product Name" << setw(10) << "Quantity"
                        << setw(15) << "Unit Price" << "Total Price" << endl;
            receiptFile << string(70, '-') << endl;

            for (size_t i = 0; i < cart.size(); ++i) {
                double total = cart[i].quantity * cart[i].product.price;
                receiptFile << left << setw(5) << i + 1 << setw(25) << cart[i].product.productName
                            << setw(10) << cart[i].quantity << setw(15) << cart[i].product.price << total << endl;
            }

            receiptFile << "\nSubtotal: " << grandTotal << " Rupees\n";
            if (discount > 0.0) {
                receiptFile << "Discount: " << discount << " Rupees\n";
            }
            receiptFile << "Final Total: " << finalTotal << " Rupees\n";
            cout << "Receipt saved successfully to 'receipt.txt'.\n";
        }
    }

    // Payment processing
    int paymentChoice;
    cout << "\nSelect Payment Method:\n";
    cout << "1. Credit Card\n";
    cout << "2. Debit Card\n";
    cout << "3. Cash\n";
    cout << "4. Digital Wallet\n";
    cout << "Enter your choice: ";
    cin >> paymentChoice;

    switch (paymentChoice) {
        case 1:
            cout << "\nProcessing payment via Credit Card...\n";
            break;
        case 2:
            cout << "\nProcessing payment via Debit Card...\n";
            break;
        case 3:
            cout << "\nProcessing payment in Cash...\n";
            break;
        case 4:
            cout << "\nProcessing payment via Digital Wallet...\n";
            break;
        default:
            cout << "\nInvalid payment method. Please try again.\n";
            return;
    }

    // Confirm before completing checkout
    char confirm;
    cout << "\nDo you confirm the checkout? (y/n): ";
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        cout << "\nThank you for your purchase! Your final total is " << finalTotal << " Rupees.\n";
    } else {
        cout << "\nCheckout canceled. Returning to the main menu.\n";
        return;
    }

    // Feedback collection
    char provideFeedback;
    cout << "\nWould you like to provide feedback about your shopping experience? (y/n): ";
    cin >> provideFeedback;

    if (provideFeedback == 'y' || provideFeedback == 'Y') {
        cin.ignore(); // Clear input buffer
        string feedback;
        cout << "\nPlease enter your feedback: ";
        getline(cin, feedback);
        ofstream feedbackFile("feedback.txt", ios::app);
        if (!feedbackFile) {
            cerr << "Failed to save feedback.\n";
        } else {
            feedbackFile << feedback << endl;
            cout << "Thank you for your feedback! It has been saved.\n";
        }
    }
}

// Function to load products from a file
// Function to load products without using files
void loadProducts(vector<RecycledProduct>& products) {
    // Predefined default products
    cout << "\nLoading default products." << endl;
    products = {
        {"Plastic", "Recycled Plastic Bag", 25.50},
        {"Metal", "Recycled Aluminum Can", 15.75},
        {"Paper", "Recycled Notebook", 35.00},
        {"Glass", "Recycled Glass Jar", 50.00},
        {"E-Waste", "Refurbished Smartphone", 3500.00}
    };

    // Optionally, allow user to add products manually
    cout << "\nWould you like to add more products manually? (y/n): ";
    char addMore;
    cin >> addMore;

    if (addMore == 'y' || addMore == 'Y') {
        while (true) {
            RecycledProduct newProduct;
            cout << "\nEnter waste type: ";
            cin.ignore();
            getline(cin, newProduct.wasteType);

            cout << "Enter product name: ";
            getline(cin, newProduct.productName);

            cout << "Enter product price: ";
            cin >> newProduct.price;

            if (!newProduct.wasteType.empty() && !newProduct.productName.empty() && newProduct.price > 0) {
                products.push_back(newProduct);
            } else {
                cout << "\nInvalid input. Product not added." << endl;
            }

            cout << "\nAdd another product? (y/n): ";
            char continueAdding;
            cin >> continueAdding;
            if (continueAdding != 'y' && continueAdding != 'Y') {
                break;
            }
        }
    }

    // Display a summary of products
    cout << "\nSummary of Products:\n";
    cout << left << setw(5) << "No." << setw(20) << "Waste Type" << setw(25) << "Product Name" << "Price (in Rupees)" << endl;
    cout << string(60, '-') << endl;
    for (size_t i = 0; i < products.size(); ++i) {
        cout << left << setw(5) << i + 1 << setw(20) << products[i].wasteType
             << setw(25) << products[i].productName << products[i].price << endl;
    }
}



// Function to save cart to a file
void saveCart(const vector<CartItem>& cart) {
    if (cart.empty()) {
        cout << "\nYour cart is empty. Nothing to save." << endl;
        return;
    }

    // Validate cart items
    bool invalidItemFound = false;
    for (const auto& item : cart) {
        if (item.quantity <= 0 || item.product.price <= 0) {
            invalidItemFound = true;
            cout << "\nInvalid item found in the cart. Skipping: "
                 << item.product.productName << " (Quantity: " << item.quantity
                 << ", Price: " << item.product.price << ")" << endl;
        }
    }

    if (invalidItemFound) {
        cout << "\nCart contains invalid items. Only valid items will be saved." << endl;
    }

    // Open file for writing
    ofstream file("cart.txt");
    if (!file) {
        cerr << "\nFailed to open file for saving the cart." << endl;
        return;
    }

    // Write cart header
    file << left << setw(25) << "Product Name" << setw(10) << "Quantity"
         << setw(15) << "Price (Rupees)" << setw(15) << "Total Price (Rupees)" << endl;
    file << string(65, '-') << endl;

    // Write each cart item
    double grandTotal = 0.0;
    for (const auto& item : cart) {
        if (item.quantity > 0 && item.product.price > 0) {
            double totalPrice = item.quantity * item.product.price;
            grandTotal += totalPrice;

            file << left << setw(25) << item.product.productName
                 << setw(10) << item.quantity
                 << setw(15) << item.product.price
                 << setw(15) << totalPrice << endl;
        }
    }

    // Write grand total
    file << string(65, '-') << endl;
    file << left << setw(50) << "Grand Total" << grandTotal << endl;

    // Log save operation
    cout << "\nCart successfully saved to 'cart.txt'." << endl;
    cout << "Summary of saved cart:" << endl;

    for (const auto& item : cart) {
        if (item.quantity > 0 && item.product.price > 0) {
            double totalPrice = item.quantity * item.product.price;
            cout << "Product: " << item.product.productName
                 << ", Quantity: " << item.quantity
                 << ", Total Price: " << totalPrice << " Rupees" << endl;
        }
    }

    cout << "Grand Total: " << grandTotal << " Rupees" << endl;
}
// Function to setup the graph
void setupGraph(ProductGraph& graph, const vector<RecycledProduct>& products) {
    for (const auto& product : products) {
        graph.addEdge(product.wasteType, product.productName);
    }
}
void loadCart(vector<CartItem>& cart, const vector<RecycledProduct>& products) {
    ifstream inFile("cart.txt"); // Open the file to read cart details
    if (!inFile) {
        cerr << "Error: Could not open file to load cart details.\n";
        return;
    }

    cart.clear(); // Clear existing cart data before loading new data

    string line;
    getline(inFile, line); // Skip header line
    getline(inFile, line); // Skip separator line

    while (getline(inFile, line)) {
        istringstream iss(line);
        string productName;
        int quantity;
        double price;

        // Read values from the line
        if (iss >> quoted(productName) >> quantity >> price) {
            // Find the corresponding product in the existing products
            auto it = find_if(products.begin(), products.end(), [&](const RecycledProduct& p) {
                return p.productName == productName && p.price == price;
            });

            if (it != products.end()) {
                cart.push_back({*it, quantity});
            } else {
                cerr << "Warning: Product '" << productName << "' not found in available products. Skipping.\n";
            }
        } else {
            cerr << "Error: Malformed line in cart file: " << line << '\n';
        }
    }

    inFile.close();
    cout << "Cart details loaded successfully from cart.txt.\n";
}

// Enhanced Error Handling
bool isValidWasteType(const string& wasteType, const vector<RecycledProduct>& products) {
    for (const auto& product : products) {
        if (product.wasteType == wasteType) return true;
    }
    return false;
}

void suggestWasteType(const vector<RecycledProduct>& products) {
    set<string> wasteTypes;
    for (const auto& product : products) {
        wasteTypes.insert(product.wasteType);
    }
    cout << "\nSuggested Waste Types: ";
    for (const auto& wasteType : wasteTypes) {
        cout << wasteType << ", ";
    }
    cout << endl;
}

// Waste-Type Connectivity Checker
bool isConnected(const ProductGraph& graph, const string& waste1, const string& waste2) {
    vector<string> neighbors = graph.getRelatedProducts(waste1);
    return find(neighbors.begin(), neighbors.end(), waste2) != neighbors.end();

}

void selectCompany() {
    cout << "\nSelect the type of company you want to buy from:" << endl;
    cout << "1. Local Small Business" << endl;
    cout << "2. National Corporation" << endl;
    cout << "3. International Brand" << endl;
    cout << "4. Eco-Friendly Certified Companies" << endl;
    cout << "Enter your choice: ";

    int companyType;
    cin >> companyType;

    switch (companyType) {
        case 1:
            cout << "\nYou chose to buy from Local Small Businesses." << endl;
            cout << "Please select a company from the list below:" << endl;
            cout << "1. Green Planet Supplies" << endl;
            cout << "2. EcoFriendly Hub" << endl;
            cout << "3. Recycle & Renew Co." << endl;
            break;
        case 2:
            cout << "\nYou chose to buy from National Corporations." << endl;
            cout << "Please select a company from the list below:" << endl;
            cout << "1. National EcoGoods" << endl;
            cout << "2. RecycleCorp Ltd." << endl;
            cout << "3. CleanEarth Solutions" << endl;
            break;
        case 3:
            cout << "\nYou chose to buy from International Brands." << endl;
            cout << "Please select a company from the list below:" << endl;
            cout << "1. Global Recycle Inc." << endl;
            cout << "2. EcoWorld Enterprises" << endl;
            cout << "3. Renewables Unlimited" << endl;
            break;
        case 4:
            cout << "\nYou chose to buy from Eco-Friendly Certified Companies." << endl;
            cout << "Please select a company from the list below:" << endl;
            cout << "1. Certified Green Co." << endl;
            cout << "2. PlanetSafe Supplies" << endl;
            cout << "3. EcoSeal Enterprises" << endl;
            break;
        default:
            cout << "\nInvalid choice. Please select a valid company type." << endl;
    }

    cout << "Enter your company choice (1-3): ";
    int companyChoice;
    cin >> companyChoice;

    switch (companyChoice)
    {
        case 1:
            cout << "\nYou selected the first company." << endl;
            break;
        case 2:
            cout << "\nYou selected the second company." << endl;
            break;
        case 3:
            cout << "\nYou selected the third company." << endl;
            break;
        default:
            cout << "\nInvalid company choice." << endl;
    }
}

int sellrecycled() {
    vector<RecycledProduct> products;
    vector<CartItem> cart;

    // Save the cart to a file
    saveCart(cart);


    ProductGraph graph;



    if (products.empty()) {
        // If no products are loaded, use default values
        cout << ".\n";
        products = {
            {"Plastic", "Recycled Plastic Bag", 25.50},
            {"Metal", "Recycled Aluminum Can", 15.75},
            {"Paper", "Recycled Notebook", 35.00},
            {"Glass", "Recycled Glass Jar", 50.00},
            {"E-Waste", "Refurbished Smartphone", 3500.00}
        };
    }


    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display Products\n";
        cout << "2. Select Product\n";
        cout << "3. View Cart\n";
        cout << "4. Checkout\n";
        cout << "5. Save Cart\n";
        cout<< "6.load cart\n";
        cout << "7. View Waste-Product Relationships\n";
        cout << "8. Select Company\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                displayProducts(products);
                break;
            case 2:
                selectProduct(products, cart);
                break;
            case 3:
                displayCart(cart);
                break;
            case 4:
                checkout(cart);
                cart.clear(); // Empty the cart after checkout
                break;
            case 5:
                saveCart(cart);
                break;
            case 6:
                loadCart(cart,products);
                break;
            case 7:
                graph.displayGraph();
                break;

            case 8:
                selectCompany();
                break;
            case 9:
                cout << "\nExiting program. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }

    }
   return 0;
}


// Route Management

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <stack>
#include <map>
#include <regex>
#include <fstream>
#include <algorithm>


class Vehicle
{
public:
    std::string vehicleModel;
    int loadCapacity;
    bool isAllotted;
    double mileage;
     // Mileage in km/l

    Vehicle(std::string model, int capacity, double mileage)
     {

        vehicleModel = model;
        loadCapacity = capacity;
        isAllotted = false;
        this->mileage = mileage;
    }

};


class Driver
 {

public:
    std::string name;
    int age;
    std::string address;
    bool isAllotted;

    Driver(std::string n, int a, std::string addr)
     {
        name = n;
        age = a;
        address = addr;
        isAllotted = false;
    }

};


class Waste
{

public:
    std::string area;
    int quantity;

    Waste(std::string a, int q)
     {
        area = a;
        quantity = q;
    }

};


// Struct to hold allocation details

struct AllocationDetail
{

    std::string vehicleModel;
    std::string driverName;
    std::string wasteArea;
    double fuelRequired;
    // Added route
    std::vector<std::string> route;

};


class BelgaumWasteManagement
{

private:
    std::vector<Vehicle> vehicles;
    std::vector<Driver> drivers;
    std::vector<Waste> wastes;
    // Graph for routes
    std::vector<std::vector<std::pair<int, int>>> graph;
    // Areas for destination
    std::vector<std::string> areas;
    // Map to store allocations by date
    std::map<std::string, std::vector<AllocationDetail>> allocations;



public:
    BelgaumWasteManagement()

    {
        // Initialize areas and graph
        areas =
         {

            "Kanabargi", "Belgaum", "Shivaji Nagar", "Tilakwadi", "Chennamma Nagar",

            "Gandhinagar", "APMC Yard", "City Market", "Fort Road", "Engg College Road",

            "Khanapur Road", "Udyambag", "Bogarves", "Goaves", "Hindwadi",

            "Mache", "Malmaruti", "Nemgoa", "Shahpur", "Sambhaji Nagar",

            "Angol", "Balekundri", "Camp", "Dharamnath", "Fort Lake"

        };


        graph =
         {

           // Kanabargi
            {{1, 10}, {2, 15}, {4, 20}},

            // Belgaum
            {{0, 10}, {3, 25}, {5, 15}},

            // Shivaji Nagar
            {{0, 15}, {3, 10}, {6, 20}},

             // Tilakwadi
            {{1, 25}, {2, 10}, {7, 30}},

            // Chennamma Nagar
            {{0, 20}, {5, 25}, {8, 15}},

             // Gandhinagar
            {{1, 15}, {4, 25}, {9, 10}},

             // APMC Yard
            {{2, 20}, {10, 25}},

            // City Market
            {{3, 30}, {11, 15}},

              // Fort Road
            {{4, 15}, {12, 20}},

             // Engg College Road
            {{5, 10}, {13, 30}},

             // Khanapur Road
            {{6, 25}, {14, 35}},

             // Udyambag
            {{7, 15}, {15, 20}},

              // Bogarves
            {{8, 20}, {16, 10}},

              // Goaves
            {{9, 30}, {17, 25}},

              // Hindwadi
            {{10, 35}, {18, 15}},

              // Mache
            {{11, 20}, {19, 10}},

            // Malmaruti
            {{12, 10}, {20, 30}},

            // Nemgoa
            {{13, 25}, {21, 15}},

            // Shahpur
            {{14, 15}, {22, 20}},

            // Sambhaji Nagar
            {{15, 10}, {23, 25}},

              // Angol
            {{16, 30}, {24, 20}},

             // Balekundri
            {{17, 15}},

              // Camp
            {{18, 20}},

              // Dharamnath
            {{19, 25}},

                // Fort Lake
            {{20, 20}}

        };

    }

    // Function to get the index of an area
    int getAreaIndex(const std::string& areaName)
     {

        for (int i = 0; i < areas.size(); i++)
          {
            if (areas[i] == areaName)
            {
                return i;
            }
        }
        // Return -1 if area is not found
        return -1;
    }


    // Add Vehicle
    void addVehicle(Vehicle v)
    {
        vehicles.push_back(v);
    }


    // Add Driver
    void addDriver(Driver d)
    {

        drivers.push_back(d);
    }


    // Add waste
    void addWaste(Waste w)
     {
        wastes.push_back(w);
    }


    // Assuming constant speed in km/h for simplicity (40 km/h)
    // average

    const double VEHICLE_SPEED = 40.0;


    // Function to calculate travel time (in hours) based on distance and speed
    double calculateTravelTime(double distance)
    {
        return distance / VEHICLE_SPEED;
    }


// Dijkstra's Algorithm for finding the shortest path from a source to a destination in a weighted graph
std::vector<int> dijkstra(int source, int destination, std::vector<int>& parent)
{

    // Initialize the number of nodes in the graph
    int n = graph.size();

    // Initialize distance vector with maximum possible values (infinity) to indicate that initially all nodes are unreachable
    std::vector<int> distance(n, std::numeric_limits<int>::max());

    // Initialize the parent vector to store the path information
    parent.assign(n, -1);

    // Distance to the source itself is always 0
    distance[source] = 0;

    // Min-heap priority queue to select the node with the smallest distance
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.push({0, source});

    // Continue until all nodes processed or priority queue is empty
    while (!pq.empty())

    {
        // Extract the node with the smallest distance
        auto [dist, node] = pq.top();
        pq.pop();

        // If the current distance is greater than the recorded distance, skip processing
        if (dist > distance[node]) continue;

        // Explore all the neighbors of the current node
        for (const auto& [neighbor, weight] : graph[node])
        {

            // Calculate new distance for the neighbor
            int newDist = distance[node] + weight;

            // If the new distance is shorter, update the distance and parent
            if (newDist < distance[neighbor])
            {
                distance[neighbor] = newDist;
                parent[neighbor] = node;

                // Push the updated distance and neighbor node into the priority queue
                pq.push({newDist, neighbor});
            }

        }

    }

    // Check if the destination is reachable
    if (distance[destination] == std::numeric_limits<int>::max())
    {
        std::cout << "No path exists from " << areas[source] << " to " << areas[destination] << "." << std::endl;
        return {};
    }

    // Return the distance vector containing shortest distances from the source to all nodes
    return distance;
}


// Function to find the longest path using modified DFS (Depth-First Search)
void findLongestPath(int source, std::vector<int>& dist, std::vector<int>& parent)
{

    // Initialize the visited vector to keep track of visited nodes
    std::vector<bool> visited(areas.size(), false);

    // Initialize the distance vector with the minimum possible values (negative infinity)
    dist.assign(areas.size(), std::numeric_limits<int>::min());

    // Initialize the parent vector to keep track of the path
    parent.assign(areas.size(), -1);

    // Distance to the source itself is always 0
    dist[source] = 0;

    // Perform DFS from each node to find the longest path
    for (int i = 0; i < areas.size(); i++)
    {
        // Start DFS from unvisited nodes
        if (!visited[i])
        {
            dfsLongestPath(i, visited, dist, parent);
        }
    }

}


// Helper function for DFS to find the longest path
void dfsLongestPath(int u, std::vector<bool>& visited, std::vector<int>& dist, std::vector<int>& parent)
{
    // Mark the current node as visited
    visited[u] = true;

    // Explore all adjacent nodes (neighbors)
    for (const auto& [v, weight] : graph[u])
    {
        // Check if the path through the current node u is longer
        if (dist[u] + weight > dist[v])
        {
            // Update the distance and parent for the neighbor node
            dist[v] = dist[u] + weight;
            parent[v] = u;
        }

        // Perform DFS on unvisited neighbors
        if (!visited[v])
        {
            dfsLongestPath(v, visited, dist, parent);
        }
    }
}


    // Function to validate date format (dd/mm/yyyy)
  bool isValidDate(const std::string& date)
{
    // Define a regular expression pattern to match dates in the format dd/mm/yyyy
    // \b asserts a word boundary to ensure the date is a complete word
    // (0[1-9]|[12][0-9]|3[01]) matches the day part, allowing values from 01 to 31
    // (0[1-9]|1[0-2]) matches the month part, allowing values from 01 to 12
    // ([0-9]{4}) matches the year part, allowing any four-digit number
    const std::regex pattern(R"(\b(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/([0-9]{4})\b)");

    // Use std::regex_match to check if the input date matches the pattern
    return std::regex_match(date, pattern);

}


    // Function to allot a vehicle for a waste collection task
    void allotVehicle(int wasteIndex)
    {

        if (wasteIndex < wastes.size())
          {
            int requiredCapacity = wastes[wasteIndex].quantity;
            std::string date;
            std::cout << "Enter the date for allotment (dd/mm/yyyy): ";
            std::cin >> date;
            while (!isValidDate(date))
             {

                std::cout << "Invalid date format. Please enter the date in the format dd/mm/yyyy: ";
                std::cin >> date;
            }

            for (int i = 0; i < vehicles.size(); i++)
              {
                if (vehicles[i].loadCapacity >= requiredCapacity && !vehicles[i].isAllotted)
                {
                    vehicles[i].isAllotted = true;
             // Assuming first driver is allotted for simplicity
                    drivers[0].isAllotted = true;
                    std::cout << "Vehicle allotted : " << vehicles[i].vehicleModel << std::endl;
                    std::cout << "  Driver name : " << drivers[0].name << " from " << drivers[0].address
                              << " for waste in " << wastes[wasteIndex].area << " on " << date << std::endl;
                    std::cout << " Driver address :" << drivers[0].address << std::endl;
                    std::cout << "Route details from Kanabargi to " << wastes[wasteIndex].area << ":\n";
                    int source = 0;  // Kanabargi
                    int destination = getAreaIndex(wastes[wasteIndex].area);

                    if (destination != -1)

                      {
                        std::vector<int> parent;
                        std::vector<int> distance = dijkstra(source, destination, parent);
                        if (distance[destination] == std::numeric_limits<int>::max())

                        {
                            std::cout << "No route found to the destination." << std::endl;
                            return;
                        }

                        std::stack<int> path;
                        std::vector<std::string> route;
                        for (int at = destination; at != -1; at = parent[at])

                          {
                            path.push(at);
                        }
                        while (!path.empty())

                        {
                            std::cout << areas[path.top()] << (path.size() > 1 ? " -> " : "");
                            route.push_back(areas[path.top()]);
                            path.pop();

                        }
                        std::cout << std::endl;

                        double totalDistance = distance[destination];
                        double travelTime = calculateTravelTime(totalDistance);
                        int hours = static_cast<int>(travelTime);
                        int minutes = static_cast<int>((travelTime - hours) * 60);

                        std::cout << "Total Distance: " << totalDistance << " km\n";

                        std::cout << "This vehicle will be free in " << hours << " hours and " << minutes << " minutes." << std::endl;

                        double fuelRequired = totalDistance / vehicles[i].mileage;

                        std::cout << "Fuel Required: " << fuelRequired << " liters\n";

                        allocations[date].push_back({vehicles[i].vehicleModel, drivers[0].name, wastes[wasteIndex].area, fuelRequired, route});

                        std::cout << " =========================================================" << std::endl;

                    }
                    else
                      {
                        std::cout << "Error: Invalid destination area." << std::endl;
                    }

                    return;
                }
            }

            std::cout << "No suitable vehicle available." << std::endl;
        }
        else
          {
            std::cout << "Invalid waste index." << std::endl;
        }

    }



void displayCollectedWasteByDate() {
    // Check if there are any waste collection records
    if (allocations.empty()) {
        std::cout << "No waste collection details available.\n";
        return;
    }

    std::cout << "=========================================================\n";
    std::cout << "             Waste Collection Details by Date            \n";
    std::cout << "=========================================================\n";

    // Iterate through each allocation date and its details
    for (const auto& [date, details] : allocations) {
        std::cout << "\nDate: " << date << "\n";
        std::cout << "---------------------------------------------------------\n";

        // Display all details for a specific date
        for (const auto& detail : details) {
            std::cout << "  Vehicle Model    : " << detail.vehicleModel << "\n";
            std::cout << "  Driver Name      : " << detail.driverName << "\n";
            std::cout << "  Waste Area       : " << detail.wasteArea << "\n";
            std::cout << "  Fuel Required    : " << detail.fuelRequired << " liters\n";
            std::cout << "  Route            : ";

            // Print the route with arrows between areas
            for (size_t i = 0; i < detail.route.size(); ++i) {
                std::cout << detail.route[i];
                if (i != detail.route.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << "\n---------------------------------------------------------\n";
        }

        std::cout << "\n=========================================================\n";
    }

    // Summary or concluding message (optional)
    std::cout << "End of waste collection records.\n";
}

void storeDataInFile()
{

    // Hardcoded file path
    std::string filename = "C:\\Users\\mahes\\OneDrive\\Desktop\\route management\\dateDATA.txt";

    // Attempt to open the file for writing
    std::ofstream outFile(filename, std::ios::out | std::ios::app);
     // Open in append mode
    if (!outFile)
      {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    // Write the header to the file
    outFile << "Collected Waste Data by Date:\n";

    // Check if there are any allocations
    if (allocations.empty())
      {
        outFile << "No waste collection data available.\n";
        std::cout << "No data to store in the file.\n";
        outFile.close(); // Close the file before returning
        return;
    }

    // Iterate over all waste collection details by date
    for (const auto& [date, details] : allocations)
      {

        outFile << "Date: " << date << "\n";
        for (const auto& detail : details)
        {

            outFile << "Vehicle Model: " << detail.vehicleModel
                    << ", Driver Name: " << detail.driverName
                    << ", Waste Area: " << detail.wasteArea
                    << ", Fuel Required: " << detail.fuelRequired << " liters\n";
            outFile << "Route: ";

            for (const auto& area : detail.route)
              {
                outFile << area << (area == detail.route.back() ? "" : " -> ");
            }
            outFile << "\n";
        }

        outFile << " ---------------------------------------------------------\n";
    }

    // Close the file and notify the user
    outFile.close();
    std::cout << "Data stored successfully in " << filename << std::endl;

}

//display the content of file

void displayFileContent(const std::string& filename)
{

    // Attempt to open the file for reading
    std::ifstream inFile(filename);
    if (!inFile)
      {
        std::cerr << "Error: Unable to open file '" << filename << "' for reading.\n";
        return;
    }

    // Display a header for better clarity
    std::cout << "=========================================================\n";
    std::cout << "                 Displaying File Content                 \n";
    std::cout << "=========================================================\n";

    // Read and display file content line by line

    std::string line;
    bool isEmpty = true;
    while (std::getline(inFile, line))

      {
        isEmpty = false;
        std::cout << line << "\n";
    }

    // Check if the file was empty
    if (isEmpty)
      {
        std::cout << "The file is empty.\n";
    }

    // Footer for better output structure
    std::cout << "=========================================================\n";
    std::cout << "                  End of File Content                    \n";
    std::cout << "=========================================================\n";

    // Close the file
    inFile.close();

}

//load content of file
// display allocation record

void loadDataFromFile(const std::string& filename)
 {
    // Attempt to open the file for reading
    std::ifstream inFile(filename);
    if (!inFile)
      {
        std::cerr << "Error: Unable to open file '" << filename << "' for reading.\n";
        return;

    }

    // Display a header for better clarity
    std::cout << "=========================================================\n";
    std::cout << "                 Displaying File Content                 \n";
    std::cout << "=========================================================\n";

    // Read and display file content line by line
    std::string line;
    bool isEmpty = true;
    while (std::getline(inFile, line))
      {

        isEmpty = false;
        std::cout << line << "\n";
    }

    // Check if the file was empty
    if (isEmpty)
      {

        std::cout << "The file is empty.\n";
    }

    // Footer for better output structure
    std::cout << "=========================================================\n";
    std::cout << "                  End of File Content                    \n";
    std::cout << "=========================================================\n";

    // Close the file
    inFile.close();

}

// diplay Menu
    void displayMenu()
     {

        std::cout << " --------------------------------------------------------------------------------------------------------" << std::endl;
        std::cout << "    " << std::endl;
        std::cout << "Belgaum City Waste Management System" << std::endl;
        std::cout << "1. Allot Vehicle" << std::endl;
        std::cout << "2. Display Vehicles" << std::endl;
        std::cout << "3. Display Drivers" << std::endl;
        std::cout << "4. Display Wastes" << std::endl;
        std::cout << "5. Shortest Route Details" << std::endl;
        std::cout << "6. Longest Route Details" << std::endl;
        std::cout << "7. View Available Vehicles and Drivers" << std::endl;
        std::cout << "8. Display Collected Waste by Date" << std::endl;
        std::cout << "9. Save Collected Waste Data to File" << std::endl;
        std::cout << "10. Load Data from File" << std::endl;
        std::cout << "11. Exit" << std::endl;
        std::cout << " ---------------------------------------------------------------------------------------------------------" << std::endl;


    }


void viewAvailableVehiclesAndDrivers()
{

    // Display header for available vehicles
    std::cout << "=========================================================\n";
    std::cout << "                   Available Vehicles                   \n";
    std::cout << "=========================================================\n";

    bool foundAvailableVehicle = false;
    for (size_t i = 0; i < vehicles.size(); i++)
      {

        if (!vehicles[i].isAllotted)
        {
            std::cout << "Vehicle Model: " << vehicles[i].vehicleModel << "\n"
                      << "  Load Capacity: " << vehicles[i].loadCapacity << " kg\n"
                      << "  Mileage: " << vehicles[i].mileage << " km/l\n";
            std::cout << "---------------------------------------------------------\n";
            foundAvailableVehicle = true;
        }
    }

    if (!foundAvailableVehicle)
      {
        std::cout << "No available vehicles at the moment.\n";
    }

    // Display header for available drivers
    std::cout << "\n=========================================================\n";
    std::cout << "                   Available Drivers                    \n";
    std::cout << "=========================================================\n";


    bool foundAvailableDriver = false;
    for (size_t i = 0; i < drivers.size(); i++)
      {
        if (!drivers[i].isAllotted)
          {

            std::cout << "Driver Name: " << drivers[i].name << "\n"
                      << "  Age: " << drivers[i].age << "\n"
                      << "  Address: " << drivers[i].address << "\n";
            std::cout << "---------------------------------------------------------\n";
            foundAvailableDriver = true;
        }
    }

    if (!foundAvailableDriver)
      {

        std::cout << "No available drivers at the moment.\n";
    }

    // Footer for better structure
    std::cout << "=========================================================\n";
    std::cout << "                  End of Availability                   \n";
    std::cout << "=========================================================\n";

}

void displayVehicles()
{

    // Display header for the vehicles section
    std::cout << "=========================================================\n";
    std::cout << "                    List of Vehicles                    \n";
    std::cout << "=========================================================\n";

    if (vehicles.empty())
      {

        std::cout << "No vehicles available in the system.\n";
    }
    else
      {

        for (int i = 0; i < vehicles.size(); i++)

        {
            std::cout << "---------------------------------------------------------\n";
            std::cout << "Vehicle " << i + 1 << ":\n";
            std::cout << "  Model: " << vehicles[i].vehicleModel << "\n"
                      << "  Load Capacity: " << vehicles[i].loadCapacity << " kg\n"
                      << "  Mileage: " << vehicles[i].mileage << " km/l\n"
                      << "  Allotted: " << (vehicles[i].isAllotted ? "Yes" : "No") << "\n";
            std::cout << "---------------------------------------------------------\n";
        }

    }

    // Display footer for the vehicles section
    std::cout << "=========================================================\n";
    std::cout << "                  End of Vehicle List                   \n";
    std::cout << "=========================================================\n";
}


void displayDrivers()
{
    // Display header for the drivers section
    std::cout << "=========================================================\n";
    std::cout << "                    List of Drivers                     \n";
    std::cout << "=========================================================\n";

    if (drivers.empty())
      {

        std::cout << "No drivers available in the system.\n";
    }
    else
      {
        for (int i = 0; i < drivers.size(); i++)
         {
            std::cout << "---------------------------------------------------------\n";
            std::cout << "Driver " << i + 1 << ":\n";
            std::cout << "  Name: " << drivers[i].name << "\n"
                      << "  Age: " << drivers[i].age << " years\n"
                      << "  Address: " << drivers[i].address << "\n";
            std::cout << "---------------------------------------------------------\n";
        }

    }

    // Display footer for the drivers section
    std::cout << "=========================================================\n";
    std::cout << "                  End of Driver List                    \n";
    std::cout << "=========================================================\n";

}

void displayWastes()
{

    // Display header for the wastes section
    std::cout << "=========================================================\n";
    std::cout << "                    Waste Information                    \n";
    std::cout << "=========================================================\n";

    if (wastes.empty())
      {

        std::cout << "No waste data available.\n";
    }
    else
      {
        for (int i = 0; i < wastes.size(); i++)
          {
            std::cout << "---------------------------------------------------------\n";
            std::cout << "Waste " << i + 1 << ":\n";
            std::cout << "  Area: " << wastes[i].area << "\n"
                      << "  Quantity: " << wastes[i].quantity << " kg\n";
            std::cout << "---------------------------------------------------------\n";
        }

    }

    // Display footer for the wastes section
    std::cout << "=========================================================\n";
    std::cout << "                   End of Waste List                    \n";
    std::cout << "=========================================================\n";
}


void findLongestRouteToDestination(int source, int destination)
{

    // Vector to store parent nodes and distances from the source node

    std::vector<int> parent;
    std::vector<int> dist;

    // Call findLongestPath to compute the longest path from the source

    findLongestPath(source, dist, parent);

    // Check if the destination is reachable from the source
    if (dist[destination] == std::numeric_limits<int>::min())
      {

        std::cout << "No path exists from " << areas[source] << " to " << areas[destination] << "." << std::endl;
        return;
    }

    // Display the longest distance to the destination
    std::cout << "Longest distance to " << areas[destination] << ": " << dist[destination] << " km" << std::endl;

    // Reconstruct and display the longest path

}

 // Existing code...

    // to simulate vehicle maintenance
    void performVehicleMaintenance()
    {
        // Placeholder for maintenance logic
    }

    //  to simulate driver training
    void conductDriverTraining()
    {
        // Placeholder for training logic
    }

    //  to simulate waste segregation
    void segregateWaste()
    {
        // Placeholder for waste segregation logic
    }

    //  simulate fuel efficiency calculation
    void calculateFuelEfficiency()
    {
        // Placeholder for fuel efficiency calculation logic
    }

    // to simulate route optimization
    void optimizeRoutes()
    {
        // Placeholder for route optimization logic
    }

    // to simulate waste disposal reporting
    void generateWasteDisposalReport()
    {
        // Placeholder for report generation logic
    }

    //  to simulate emergency response
    void handleEmergencySituation()
    {
        // Placeholder for emergency handling logic
    }

    //  to simulate vehicle tracking
    void trackVehicles()
    {
        // Placeholder for vehicle tracking logic
    }

    // to simulate driver feedback collection
    void collectDriverFeedback()
    {
        // Placeholder for feedback collection logic
    }

    // to simulate waste collection scheduling
    void scheduleWasteCollection()
    {
        // Placeholder for scheduling logic
    }

    // all remaining functions

//calculate shortest route
// use of dijkastra algorithm
void findShortestRouteToDestination(int source, int destination)
{
    std::vector<int> parent;

    // Compute the shortest distances and parent paths using Dijkstra's algorithm
    auto distances = dijkstra(source, destination, parent);

    // Check if the destination is reachable from the source
    if (distances[destination] == std::numeric_limits<int>::max())
      {

        std::cout << "No path exists from " << areas[source] << " to " << areas[destination] << "." << std::endl;
        return;
    }

    // Display the shortest distance to the destination
    std::cout << "Shortest distance to " << areas[destination] << ": " << distances[destination] << " km" << std::endl;

    // Display the shortest route from source to destination
    std::cout << "Route: ";

    std::stack<int> path;

    for (int at = destination; at != -1; at = parent[at])
      {
        path.push(at);
    }

    // Output the path from source to destination in human-readable format
    while (!path.empty())
    {

        std::cout << areas[path.top()] << (path.size() > 1 ? " -> " : "");
        path.pop();
    }

    std::cout << std::endl;

    // Calculate and display additional travel information
    //in hr and min

    double totalDistance = distances[destination];

    double travelTime = calculateTravelTime(totalDistance);

    // Extract hours and minutes from the travel time

    int hours = static_cast<int>(travelTime);

    int minutes = static_cast<int>((travelTime - hours) * 60);


    // Display the travel time and other relevant information

    std::cout << " =========================================================" << std::endl;

    std::cout << "Total Distance: " << totalDistance << " km\n";

    // Display the estimated travel time in hours and minutes

    std::cout << "Estimated Travel Time: " << hours << " hours and " << minutes << " minutes." << std::endl;



    // Additional informative output for the user


    std::cout << "\nPlease ensure the vehicle is ready for travel and has sufficient fuel." << std::endl;

    std::cout << "Remember to check the weather and road conditions before starting the journey." << std::endl;

    // Conclusion message

    std::cout << " =========================================================" << std::endl;

}

};


int route()

{
    BelgaumWasteManagement bwm;

    // Add Vehicles
    //vehicle1

    bwm.addVehicle(Vehicle("Tata Ace", 1000, 13.0));

    //vehicle2

    bwm.addVehicle(Vehicle("Mahindra Pickup", 2000, 12.0));

    //vehicle3

    bwm.addVehicle(Vehicle("Ashok Leyland Dost", 3000, 14.0));

    //vehicle4

    bwm.addVehicle(Vehicle("BharatBenz 1160", 4000, 11.0));

    //vehicle5
    bwm.addVehicle(Vehicle("Eicher 950", 6000, 12.0));
    //vehicle6
    bwm.addVehicle(Vehicle("Tata Ace Hybrid", 9000, 11.0));
    //vehicle7
    bwm.addVehicle(Vehicle("Tata Force", 10000, 10.0));
    //vehicle8
    bwm.addVehicle(Vehicle("Leyland Bada Dost", 11000, 9.0));
    //vehicle9
    bwm.addVehicle(Vehicle("MAN 1600", 12000, 8.0));
    //vehicle10
    bwm.addVehicle(Vehicle("Tata 1630", 14000, 7.0));
    //All vehicle


    // Add Drivers



    // All drivers

    bwm.addDriver(Driver("Abhi", 30, "Gokak"));
    bwm.addDriver(Driver("Arun", 32, "Hubli"));
    bwm.addDriver(Driver("Akash", 25, "Kanabargi"));
    bwm.addDriver(Driver("Gagan", 28, "Sambre"));
    bwm.addDriver(Driver("Venki", 26, "Suldal"));

    // Add Wastes
    //wastearea1
    bwm.addWaste(Waste("Kanabargi", 500));

    //wastearea2
    bwm.addWaste(Waste("BelgaumCBT", 1000));


    //wastearea3
    bwm.addWaste(Waste("Shivaji Nagar", 1500));
    //wastearea4
    bwm.addWaste(Waste("Tilakwadi", 2000));

    //wastearea5
    bwm.addWaste(Waste("Chennamma Nagar", 2500));

    //wastearea6
    bwm.addWaste(Waste("Gandhinagar", 3000));

    //wastearea7
    bwm.addWaste(Waste("APMC Yard", 3500));

    //wastearea8
    bwm.addWaste(Waste("City Market", 4000));

    //wastearea9
    bwm.addWaste(Waste("Fort Road", 4500));

    //wastearea10
    bwm.addWaste(Waste("Engg College Road", 5000));

    //wastearea11
    bwm.addWaste(Waste("Khanapur Road", 5500));

    //wastearea12
    bwm.addWaste(Waste("Udyambag", 6000));

    //wastearea13
    bwm.addWaste(Waste("Bogarves", 6500));


    //wastearea14
    bwm.addWaste(Waste("Goaves", 7000));

    //wastearea15
    bwm.addWaste(Waste("Hindwadi", 7500));

    //wastearea16
    bwm.addWaste(Waste("Mache", 8000));

    //wastearea17
    bwm.addWaste(Waste("Malmaruti", 8500));

    //wastearea18
    bwm.addWaste(Waste("Nemgoa", 9000));

    //wastearea19
    bwm.addWaste(Waste("Shahpur", 9500));

    //wastearea20
    bwm.addWaste(Waste("Sambhaji Nagar", 10000));

    //wastearea21
    bwm.addWaste(Waste("Angol", 10500));

    //wastearea22
    bwm.addWaste(Waste("Balekundri", 11000));

    //wastearea23
    bwm.addWaste(Waste("Camp", 11500));
    //wastearea24
    bwm.addWaste(Waste("Dharamnath", 12000));

    //wastearea25
    bwm.addWaste(Waste("Fort Lake", 12500));


    int choice;

    do
      {

        bwm.displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;


        // Handle invalid input for menu choice
        if(std::cin.fail())
          {
            std::cin.clear();
             // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // ignore invalid input
            std::cout << "Invalid input. Please enter a valid number.\n";
            continue;

        }

        switch (choice)
         {

        case 1:
          {

            int wasteIndex;
             std::cout << "Enter destination area index:\n";
              std::cout << "1: Kanabargi\n";
              std::cout << "2: Belgaum\n";
              std::cout << "3: Shivaji Nagar\n";
              std::cout << "4: Tilakwadi\n";
              std::cout << "5: Chennamma Nagar\n";
              std::cout << "6: Gandhinagar\n";
              std::cout << "7: APMC Yard\n";
              std::cout << "8: City Market\n";
              std::cout << "9: Fort Road\n";
              std::cout << "10: Engg College Road\n";
              std::cout << "11: Khanapur Road\n";
              std::cout << "12: Udyambag\n";
              std::cout << "13: Bogarves\n";
              std::cout << "14: Goaves\n";
              std::cout << "15: Hindwadi\n";
              std::cout << "16: Mache\n";
              std::cout << "17: Malmaruti\n";
              std::cout << "18: Nemgoa\n";
              std::cout << "19: Shahpur\n";
              std::cout << "20: Sambhaji Nagar\n";
              std::cout << "21: Angol\n";
              std::cout << "22: Balekundri\n";
              std::cout << "23: Camp\n";
              std::cout << "24: Dharamnath\n";
              std::cout << "25: Fort Lake\n";
            std::cin >> wasteIndex;
            if(wasteIndex < 1 || wasteIndex > 25)
              {

                std::cout << "Invalid waste index. Please enter a number between 1 and 25.\n";
            }
            else
              {

                bwm.allotVehicle(wasteIndex - 1);
            }

            break;
        }


        case 2:
            bwm.displayVehicles();
            break;


        case 3:
            bwm.displayDrivers();
            break;


        case 4:
            bwm.displayWastes();
            break;


        case 5:
           {

            int destination;
            std::cout << "Enter destination area index (1: Kanabargi, 2: Belgaum, 3: Shivaji Nagar, ... 25: Fort Lake): ";

            std::cin >> destination;

            if(destination < 1 || destination > 25)
              {

                std::cout << "Invalid destination. Please enter a number between 1 and 25.\n";

            }
             else
              {

                int source = 0; // Kanabargi
                bwm.findShortestRouteToDestination(source, destination - 1);
            }
            break;
        }


        case 6:
          {

            int destination;
           std::cout << "Enter destination area index:\n";
              std::cout << "1: Kanabargi\n";
              std::cout << "2: Belgaum\n";
              std::cout << "3: Shivaji Nagar\n";
              std::cout << "4: Tilakwadi\n";
              std::cout << "5: Chennamma Nagar\n";
              std::cout << "6: Gandhinagar\n";
              std::cout << "7: APMC Yard\n";
              std::cout << "8: City Market\n";
              std::cout << "9: Fort Road\n";
              std::cout << "10: Engg College Road\n";
              std::cout << "11: Khanapur Road\n";
              std::cout << "12: Udyambag\n";
              std::cout << "13: Bogarves\n";
              std::cout << "14: Goaves\n";
              std::cout << "15: Hindwadi\n";
              std::cout << "16: Mache\n";
              std::cout << "17: Malmaruti\n";
              std::cout << "18: Nemgoa\n";
              std::cout << "19: Shahpur\n";
              std::cout << "20: Sambhaji Nagar\n";
              std::cout << "21: Angol\n";
              std::cout << "22: Balekundri\n";
              std::cout << "23: Camp\n";
              std::cout << "24: Dharamnath\n";
              std::cout << "25: Fort Lake\n";
            std::cin >> destination;
            if(destination < 1 || destination > 25)
              {

                std::cout << "Invalid destination. Please enter a number between 1 and 25.\n";
            }
            else
              {
                int source = 0;
                // Kanabargi

                bwm.findLongestRouteToDestination(source, destination - 1);
            }

            break;
        }

        case 7:
            bwm.viewAvailableVehiclesAndDrivers();
            break;


        case 8:
            bwm.displayCollectedWasteByDate();
            break;


        case 9:
            bwm.storeDataInFile();

            break;



        case 10:

          {

            std::string filename = "C:\\Users\\mahes\\OneDrive\\Desktop\\route management\\dateDATA.txt";
            //file path


            bwm.loadDataFromFile(filename);
            break;
        }



        case 11:
            std::cout << "Exiting the program." << std::endl;
            break;

        default:

            std::cout << "Invalid choice. Please try again." << std::endl;
        }


    } while (choice != 11);


    return 0;


}
