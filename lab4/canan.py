import math
import matplotlib.pyplot as plt
import random

# Function to calculate the height of the projectile at time t
def calculate_height(v, t, angle_rad):
    g = 32.174  # Acceleration due to gravity in ft/s²
    return v * t * math.cos(angle_rad) - 0.5 * g * t**2

# Function to calculate the horizontal distance at time t
def calculate_distance(v, t, angle_rad):
    return v * t * math.sin(angle_rad)

# Function to plot the trajectory of the projectile
def plot_trajectory(v, angle_deg):
    g = 32.174
    angle_rad = math.radians(angle_deg)  # Convert degrees to radians

    total_flight_time = (2 * v * math.cos(angle_rad)) / g
    times = []
    heights = []
    distances = []

    # Calculate the projectile's position at different times
    t = 0
    while t <= total_flight_time:
        height = calculate_height(v, t, angle_rad)
        distance = calculate_distance(v, t, angle_rad)
        if height < 0:
            break
        times.append(t)
        heights.append(height)
        distances.append(distance)
        t += 0.1  # More frequent points for a smoother curve

    # Plot the distance vs height for trajectory
    plt.plot(distances, heights)
    plt.xlabel('Distance (feet)')
    plt.ylabel('Height (feet)')
    plt.title(f'Trajectory at {angle_deg} degrees')
    plt.grid(True)
    plt.show()

# Function to check if the projectile hit the target
def hit_target(v, angle_deg, target_position):
    g = 32.174
    angle_rad = math.radians(angle_deg)
    total_flight_time = (2 * v * math.cos(angle_rad)) / g

    # Check the horizontal distance at each time step
    t = 0
    while t <= total_flight_time:
        distance = calculate_distance(v, t, angle_rad)
        if abs(distance - target_position) < 10:  # Hit tolerance within 10 feet
            return True
        t += 0.1
    return False

# Main game function
def cannon_game():
    target_position = random.randint(100, 500)  # Random target distance in feet
    print(f"Target is at {target_position} feet")

    attempts = 3  # Number of attempts the user gets to hit the target

    for attempt in range(attempts):
        print(f"Attempt {attempt + 1} of {attempts}")
        v = float(input("Enter the initial velocity (in feet per second): "))
        angle = float(input("Enter the angle (in degrees): "))

        # Plot the trajectory of the cannonball
        plot_trajectory(v, angle)

        # Check if the projectile hits the target
        if hit_target(v, angle, target_position):
            print(f"Hit! You hit the target at {target_position} feet.")
            break
        else:
            print("Miss! Try again.")
    else:
        print(f"You've used all your attempts. The target was at {target_position} feet.")

# Run the game
if __name__ == "__main__":
    cannon_game()
