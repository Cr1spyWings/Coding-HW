"""
CS 118 The best roadtrip ever - CS118 Final Project
Author: Chris Wong
"""

from json import load
from itertools import permutations, combinations_with_replacement

def avg_temp(route: tuple) -> float:
    """
    Calculating the average temp of a route
    :param route: list of cities
    :return: avg temp
    """
    total_temp, day = 0, 1
    for name in range(len(route)):
        total_temp += route[name]['temperatures'][day - 1]
        day += 1
    return total_temp / len(route)

def hotel_costs(hotels: tuple) -> int:
    """
    Hotel cost total
    :param hotels: list of hotel names like:
    :return: sum of the per night cost
    """
    global hotel_rates
    total_cost = sum(hotel_rates[the_hotel] for the_hotel in hotels)
    return total_cost if total_cost < hotel_budget else 0

def rte_len(route: tuple, closed: bool = False) -> int:
    """
    Calculating the length of a route
    :param route: list of cities
    :param closed: True, means closing the loop, going back from the last location to the start.
    :return: length of a closed route (i.e., returning to the start)
    """
    total_dist = 0
    for a_city in range(len(route) - 1):
        total_dist += route[a_city]['distances']
        if closed:
            total_dist += route[a_city][0]
            closed = False
    return total_dist

def rte_to_str(route: tuple, closed: bool = False) -> str:
    """
    String representation of a route
    :param route: list of cities
    :param closed: True, means closing the loop, going back from the last location to the start.
    :return: A string showing the intermediate points separated by '->'
    """
    result, lst_of_route = "", list(route[name] for name in range(len(route)))
    if closed:
        lst_of_route.append(route[0])
    for item in lst_of_route:
        result += str(item['name']) + "->"
    return result

with open("city_temp_dist.json") as file:  # load json structure representing a list of dictionaries
    cities = load(file)  # city list
with open("hotel_rates.json") as file:  # load json structure representing a dictionary
    hotel_rates = load(file)  # hotel dictionary

average_temps, the_route = [], ""
hotel_budget, hotel_names, best_hotel_cost = 850, [n for n in hotel_rates.keys()], 0
route_lengths, highest_avg = [], lambda t: max(t)

# for finding the best route of cities and the shortest route
rand_city_list = list(permutations(cities))
for city in rand_city_list:
    average_temps.append(avg_temp(city))
    route_lengths.append(rte_len(city, closed=True))
best_route = rand_city_list[average_temps.index((highest_avg(average_temps)))]
print(f"The best route is {rte_to_str(best_route, closed=False)[:-2]}. The average daily maximum temperature is {highest_avg(average_temps)}.")

# for finding the best combination of hotels
hotel_combos = list(combinations_with_replacement(hotel_rates, len(cities)))
hotel_prices = max(hotel_combos, key=hotel_costs)
best_hotel_combo = hotel_combos[0]
print(f"To max out your hotel budget, stay at these hotels: {best_hotel_combo}, totalling ${hotel_prices}.")

shortest_route = rand_city_list[route_lengths.index(min(route_lengths))]
print(f"The shortest loop: {rte_to_str(shortest_route, closed=True)[:-2]} is {min(route_lengths)} miles long.")
