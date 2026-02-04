"""
IDK, maybe code a game or smthn

"""
""" Player & Game Stats"""
room_items = []
next_rooms = {}
player_health = 30
player_inventory = ["sword", "healing potion"]
player_actions = ["move", "attack", "check", "look", "grab", "heal", "help", "leave"]
boss_status = "alive"

"""Intro command"""
def intro_question():
    answer = input("Are you up to the task? yes/no: ")
    return True if answer == "yes" else False

# ---------------------------------------------------------------------------------------------------------------------
""" Player actions"""
def move():
    global room
    print(f"Your legal moves are {rooms_next_to()}")
    direc = str(input("which direction would u like to move? "))
    legal_move = rooms_next_to()
    print(legal_move.values())
    print(legal_move.keys())
    if direc in legal_move.values():
        room = legal_move.get(legal_move, [])
        print(room)
        eval(room + "()")
        return room
    else:
        return "That is not a legal movement"

def attack():
    return

def check():
    print(f"You have {player_inventory} in your inventory.")
    print(f"There are {check_room_items()} item in this room.")

def look():
    print(f"There is a {room_items} in this room.")

def grab():
    print(f"There are {check_room_items()} item in this room.")
    item_to_grab = str(input("What would you like to grab? "))
    if item_to_grab in check_room_items():
        player_inventory.append(item_to_grab)
        room_items.remove(item_to_grab)
    else:
        print("That item is not in the room.")

def heal():
    global player_health
    health = get_health()
    if health >= 30:
        player_health = 30
        print(f"{player_name} is now at {player_health} HP.")
    elif health < 30:
        player_health += 5
        player_inventory.remove("healing potion")
    return

def help():
    print(f"Your actions are, {player_actions}.")

def leave():
    global game_start
    game_start = False
    return game_start

def get_health():
    return player_health

def action(player_act):
    return player_act()

# ---------------------------------------------------------------------------------------------------------------------
""" Different Rooms"""
def start_room():
    global room_items
    global next_rooms
    print("You spawn in a large room with wall all around you.")
    print("There is nothing in this room, and the only items you have on you are a sword and a healing potions.")
    print("A single door in front of you appears to be your only way forward.")
    room_items = []
    next_rooms = {"main_room": "up"}
    return "start_room"

def main_room():
    global room_items
    global next_rooms
    print("You walk into a big open room.")
    print("There doesn't appear to be anything in the room, but you have a hunch there may be.")
    print("You see there is a large door in front of you, and a smaller door off to your right.")
    room_items = []
    next_rooms = {"boss_room": "up", "start_room": "down", "treasure_room": "right"}
    return "main_room"

def treasure_room():
    global room_items
    global next_rooms
    room_items = ["gold", "jewels"]
    next_rooms = {"main_room": "left"}
    return "treasure_room"

def boss_room():
    global room_items
    global next_rooms
    room_items = ["greatsword", "healing potion"]
    next_rooms = {"main_room": "down"}
    return "boss_room"

def get_room():
    return room

def check_room_items():
    get_room()
    return room_items

def rooms_next_to():
    return next_rooms

# ---------------------------------------------------------------------------------------------------------------------
"""Game Code"""
player_name = str(input("Enter your name: "))
print(f"Welcome, {player_name}, to ...!")
print("You have been tasked by some programmer to find a jewel that they have hidden within this game.")
game_start = intro_question()
room = start_room()
while game_start:
    print(room)
    room = get_room()
    eval(room)
    act = input("What would you like to do? type 'help' if you need help. ")
    if act in player_actions:
        eval(act + "()")
    else:
        print(f"That is not a legal action {player_name}! Maybe restarting the game will help you find a legal action.")
        game_start = False

if boss_status == "alive":
    print("You didn't defeat the boss. Did you not do something correctly?")
else:
    print(f"You defeated the boss and got the jewel! Good Job {player_name}")
print(f"Thanks for playing {player_name}! See you next time!")
