import os
import random
import time

maze = [
    list("###############"),
    list("#P....#.......#"),
    list("#.###.#.#####.#"),
    list("#.....#...#...#"),
    list("#####.###.#.###"),
    list("#.........#...#"),
    list("#.#####.#####.#"),
    list("#...........G.#"),
    list("###############")
]

ROWS = len(maze)
COLS = len(maze[0])

def find_entity(symbol):
    for r in range(ROWS):
        for c in range(COLS):
            if maze[r][c] == symbol:
                return r, c

pacman_r, pacman_c = find_entity("P")
ghost_r, ghost_c = find_entity("G")

def clear():
    os.system("cls" if os.name == "nt" else "clear")

def draw():
    clear()
    for row in maze:
        print("".join(row))
    print("\nControls: W = Up, S = Down, A = Left, D = Right, Q = Quit")

def dots_left():
    return sum(row.count(".") for row in maze)

def move_pacman(dr, dc):
    global pacman_r, pacman_c

    new_r = pacman_r + dr
    new_c = pacman_c + dc

    if maze[new_r][new_c] == "#":
        return
                                                                                                                                                                            
    maze[pacman_r][pacman_c] = " "
    pacman_r, pacman_c = new_r, new_c
    maze[pacman_r][pacman_c] = "P"

def move_ghost():
    global ghost_r, ghost_c

    directions = [(1,0), (-1,0), (0,1), (0,-1)]
    random.shuffle(directions)

    for dr, dc in directions:
        new_r = ghost_r + dr
        new_c = ghost_c + dc
        
        if maze[new_r][new_c] != "#":                          
            maze[ghost_r][ghost_c] = " "
            ghost_r, ghost_c = new_r, new_c
            maze[ghost_r][ghost_c] = "G"
            return

"""
MAIN GAME LOOP
"""
while True:
    draw()

    if dots_left() == 0:
        print("\nYOU WIN!")
        break

    move = input("\nYour move: ").lower()

    if move == "q":
        print("Exiting game.")
        break
    if move == "w":
        move_pacman(-1, 0)
    elif move == "s":
        move_pacman(1, 0)
    elif move == "a":
        move_pacman(0, -1)
    elif move == "d":
        move_pacman(0, 1)

    move_ghost()

    if pacman_r == ghost_r and pacman_c == ghost_c:
        draw()
        print("GAME OVER")
        break

    time.sleep(0.2)
