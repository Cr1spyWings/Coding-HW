"""
IDK, maybe code a game or smthn

"""
import random

""" Player & Game Stats"""
room_items = []
next_rooms = {}
player_health = 30
player_inventory = ["sword", "healing potion"]
player_actions = ["move", "attack", "check", "look", "grab", "heal", "help", "leave"]
sword_atk = 3
greatsword_atk = 5
boss_alive = True
boss_HP = 25
boss_maxHP = 35
boss_ATK = 4
first_bossR_ent = 0

"""Intro command"""
def intro_question():
    answer = input("Are you up to the task? yes/no: ").lower()
    return True if answer == "yes" or "y" else False

# ---------------------------------------------------------------------------------------------------------------------
""" Player actions"""
def move():
    global room, first_bossR_ent
    print(f"Your legal moves are {rooms_next_to()}")
    direc = input("which direction would u like to move? ").lower()
    legal_move = rooms_next_to()
    for next_room, direction in legal_move.items():
        if direc == direction:
            room = next_room
            rooms[room]()
            return room
    else:
        return "That is not a legal movement"

def attack():
    global atk_item
    global boss_HP
    global boss_maxHP
    if room != "boss_room":
        print("There is nothing to attack here")
    else:
        print(player_inventory)
        atk_item = input("Which item would you like to attack with? ")
        if atk_item not in player_inventory:
            print("You do not have this item...")
        if atk_item in ["healing potion"]:
            print("Why would this be a good idea?")
            print("Boss's HP has increaed by 5")
            if boss_HP <= boss_maxHP:
                boss_HP += 5
                if boss_HP >= boss_maxHP:
                    boss_HP = boss_maxHP
            player_inventory.remove(atk_item)
        if atk_item in ["sword", "greatsword"]:
            if atk_item == "sword":
                print(f"You hit the orc for {sword_atk} damage")
                boss_HP -= sword_atk
            else:
                print(f"You hit the orc for {greatsword_atk} damage")
                boss_HP -= greatsword_atk
        if atk_item not in ["healing potion", "sword", "greatsword"]:
            print("This item cannot be used here")
    return

def check():
    print(f"You have {player_inventory} in your inventory.")

def look():
    if room_items:
        print(f"There is a {room_items} in this room.")
    else:
        print("There is nothing in this room.")
    
def grab():
    print(f"There are {check_room_items()} item in this room.")
    item_to_grab = str(input("What would you like to grab? "))
    if item_to_grab in check_room_items():
        print(f"You grabbed {item_to_grab}")
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
# --------------------------------------------------------------------------------------------------------------------
def boss_act():
    global boss_HP, boss_alive, boss_maxHP, boss_ATK, player_health
    if not boss_alive:
        return
    action = random.choice(["attack", "heal", "loaf"])
    if action == "attack":
        player_health -= boss_ATK
        print(f"The orc smacks you for {boss_ATK} damage")
        print(f"You now have {player_health} HP")
    elif action == "heal":
        boss_HP += 4
        if boss_HP > boss_maxHP:
            bossHP = boss_maxHP
        print("The orc heals its wounds.")
    else:
        print("The orc watches you, waiting for your next move...")

    if boss_HP <= 0:
        boss_alive = False
        print("The orc falls to the ground. You have emerged victorious!")
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
    print("There is a large orc guarding the exit to this room. If you don't defeat him, you will not be able to leave")
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

rooms = {
    "start_room": start_room,
    "main_room": main_room,
    "treasure_room": treasure_room,
    "boss_room": boss_room
}
# ---------------------------------------------------------------------------------------------------------------------
"""Game Code"""
player_name = str(input("Enter your name: "))
print(f"Welcome, {player_name}, to ...!")
print("You have been tasked by some programmer to find a jewel that they have hidden within this game.")
game_start = intro_question()
room = start_room()
while game_start:
    room = get_room()
    print(f"\nYou are in {room}")
    eval(room)
        
    act = input("What would you like to do? type 'help' if you need help. ")
    if act in player_actions:
        eval(act + "()")
        
        if room == "boss_room" and boss_alive:
            if first_bossR_ent == 0:
                first_bossR_ent+= 1
            else:
                boss_act()
    else:
        print(f"That is not a legal action {player_name}! Maybe restarting the game will help you find a legal action.")
        game_start = False
    print()

    if not boss_alive:
        game_start = False

if boss_alive:
    print("You didn't defeat the boss. Did you not do something correctly?")
else:
    print(f"You defeated the boss and got the jewel! Good Job {player_name}")
    print("You are now able to leave this dungeon and return to your life.")
print(f"Thanks for playing {player_name}! See you next time!")
