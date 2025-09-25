import time
import random

width = 7
player_pos = width // 2
score = 0

print("🎮 Welcome to Dodge the Falling Rocks!")
print("Controls: 'a' to move left, 'd' to move right. Press Enter to start.")
input()

while True:
    # Generate row
    rock_pos = random.randint(0, width - 1)
    row = [' '] * width
    row[rock_pos] = 'O'

    # Draw row and player
    for i in range(width):
        if i == player_pos:
            print('😃', end='')
        else:
            print(row[i], end='')
    print()

    # Check collision
    if player_pos == rock_pos:
        print("💥 You got hit! Final score:", score)
        break

    # Move player
    move = input("Move (a/d): ")
    if move == 'a' and player_pos > 0:
        player_pos -= 1
    elif move == 'd' and player_pos < width - 1:
        player_pos += 1

    score += 1
    print("-" * width)
