#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class CP_manager{
    // Class for keeping checkpoints in memory. Aim is to find the longest stretch on the path
    // and use boost there
    public:
        vector<vector<int>> CPs;  // A vector of chekpoints visited
        vector<int> best_CP;  // The checkoint for when best to use boost

        int get_distance(vector<int> point1, vector<int> point2){
            return pow(point1[0] - point2[0],2) + pow(point1[1] - point2[1], 2);
        }

        void get_best_CP_for_boost(vector<vector<int>> locations){
            // Iterate through all points and return the CP that is the endpoint 
            // for the longest stretch
            int max_distance = 0;
            for (int i = 0; i < size(locations)-1; i++){
                vector<int> loc1 = locations[i];  // Start point of stretch
                vector<int> loc2 = locations[i+1];  // End point of stretch
                int distance = get_distance(loc1, loc2);
                if (distance > max_distance){ 
                    max_distance = distance;
                    best_CP = locations[i+1];
                }
            }
        }

        void manage(int x,int y){
            // Initialise checkpoint
            vector<int> CP{x,y};

            if(std::find(CPs.begin(), CPs.end(), CP) != CPs.end()) {
                // CP has already been passed
                // Calculate the best CP for using boost
                get_best_CP_for_boost(CPs);
            } 
            else {
                // New CP, which hasn't been visited before. First lap is still ongiong
                // Update CPs
                CPs.push_back(CP);
            }
        }
};

bool Check_boost(vector<int> best_point, vector<int> next_point, int angle){
    // Checks if the pod is in a place to use boost by determining if it is on the longest
    // stetch and if the pod is pointing towards the next CP

    /*
    NOTE: For some reason this function never returns true. Got promoted to gold before
    I could fix it
    */
    
    
    if (next_point == best_point and angle < 10 and angle > -10){
        return true;
    }
    else{
        return false;
    }
};

string Thrust_managment(int angle, int distance){
    // If the pod is pointing almost straight at the target then apply max thrust
    // otherwise scale down the thrust in proprtion to how close to the target the pod is (slows down slightly)
    // and how misaligned with the target the pod is. This stops the pod from shooting off in the wrong direction  
    string thrust;
    if (angle <= 10){
        thrust = to_string(100);
    }
    else{
        thrust = to_string(100*clamp(0,1,1-angle/90)*clamp(0,1,distance/1200));
    }
    return thrust;
};

vector<int> add_vectors(vector<int> v1, vector<int> v2){
    // Helper function for adding vectors
    // Vectors must be the same size
    vector<int> v;
    if (size(v1) != size(v2)){
        return v;
    }
    else{
        for (int i=0; i < size(v1);i++){
            v[i] = v1[i] + v2[i];

        }
        return v;
    }
}


vector<int> Manage_offset(int x, int y, int current_x, int current_y, int last_x, int last_y){
    // Move the target of the pod by applying an offset
    // A sketch of the idea is in the Readme file on git
    // Aim is to make the pod steer more 
    int magnitude_correction = 2;
    int dx = current_x - last_x;
    int dy = current_y - last_y;
    int new_x = x - magnitude_correction*dx;
    int new_y = y - magnitude_correction*dy;
    vector<int> CP{new_x,new_y};
    return CP;
};

int main()
{
    CP_manager pod_CP;
    vector<int> last_turn_CP({-1,-1});  // The checkpoint that the pod was travelling towards last turn
    bool boost_available = true;  // Only check for boost once per race 
    vector<int> CP_for_boost;  // The CP to be used for boost
    vector<int> adjusted_CP;  // A point with an offset for better steering
    int last_x;
    int last_y;
    
    // game loop
    while (1) {
        int x;
        int y;
        int next_checkpoint_x; // x position of the next check point
        int next_checkpoint_y; // y position of the next check point
        int next_checkpoint_dist; // distance to the next checkpoint
        int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; cin.ignore();
        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();
        string thrust;
        

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        if (last_turn_CP[0] != next_checkpoint_x or last_turn_CP[1] != next_checkpoint_y){
            // CP has changed. The pod is now travelling towards a new CP
            pod_CP.manage(next_checkpoint_x, next_checkpoint_y);  // 
            CP_for_boost = pod_CP.best_CP;
        }

        // Check if to use boost based on the angle and which CP the pod is travelling towards
        bool check = Check_boost(CP_for_boost, last_turn_CP, next_checkpoint_angle); 
    
        if (boost_available == false){
            // manage thrust
            thrust = Thrust_managment(next_checkpoint_angle,next_checkpoint_dist);
        }

        if (boost_available == true and check == true){
                boost_available = false;
                thrust = "BOOST";
        }
        
        adjusted_CP = Manage_offset(next_checkpoint_x,next_checkpoint_y,x,y,last_x,last_y);
        // You have to output the target position
        // followed by the power (0 <= thrust <= 100)
        // i.e.: "x y thrust"

        // Keep info about last turn in memory
        last_turn_CP[0] = next_checkpoint_x;
        last_turn_CP[1] = next_checkpoint_y;
        // posistion of the pod last turn
        last_x = x;  
        last_y = y;

        cout << adjusted_CP[0] << " " << adjusted_CP[1] << " " << thrust << endl;
    }
}