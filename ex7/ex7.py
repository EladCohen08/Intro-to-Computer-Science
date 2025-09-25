"""
 * Name: Elad
 * ID: 331526079
 * Assignment: ex7
"""

import csv

ownerRoot = None


########################
# 0) Read from CSV -> HOENN_DATA
########################

# Reads pokemon data from a file
def read_hoenn_csv(filename):
    """
    Reads 'hoenn_pokedex.csv' and returns a list of dicts:
      [ { 'ID': int, 'Name': str, 'Type': str, 'HP': int,
          'Attack': int, 'Can Evolve': "TRUE"/"FALSE" },
        ... ]
    """
    data_list = []
    with open(filename, mode='r', encoding='utf-8') as f:
        reader = csv.reader(f, delimiter=',')  # Use comma as the delimiter
        first_row = True
        for row in reader:
            # It's the header row (like ID,Name,Type,HP,Attack,Can Evolve), skip it
            if first_row:
                first_row = False
                continue

            # row => [ID, Name, Type, HP, Attack, Can Evolve]
            if not row or not row[0].strip():
                break  # Empty or invalid row => stop
            d = {
                'ID': int(row[0]),
                'Name': str(row[1]),
                'Type': str(row[2]),
                'HP': int(row[3]),
                'Attack': int(row[4]),
                'Can Evolve': str(row[5]).upper()
            }
            data_list.append(d)
    return data_list


HOENN_DATA = read_hoenn_csv("hoenn_pokedex.csv")


########################
# 1) Helper Functions
########################

# Prompt the user for an integer, re-prompting on invalid input.
def read_int_safe(prompt):
    while True:
        choice = input(prompt).strip()
        # Check if the input is a valid integer
        if choice.lstrip('-').isdigit():  # Remove negative sign and check if num
            return int(choice) # Convert to integer and return
        else:
            print("Invalid input.\n")


# Return a copy of the Pokemon dict from HOENN_DATA by name, or None if not found.
def get_poke_dict_by_id(pokemon_id):
    # Check if pokemon_id is in range
    if pokemon_id < 1 or pokemon_id > len(HOENN_DATA):
        print(f"ID {pokemon_id} not found in Honen data.\n")
        return None

    pokemon = {
        'ID': pokemon_id,
        'Name': HOENN_DATA[pokemon_id - 1]['Name'],
        'Type': HOENN_DATA[pokemon_id - 1]['Type'],
        'HP': HOENN_DATA[pokemon_id - 1]['HP'],
        'Attack': HOENN_DATA[pokemon_id - 1]['Attack'],
        'Can Evolve': HOENN_DATA[pokemon_id - 1]['Can Evolve']
    }
    return pokemon


# Return a copy of the Pokemon dict from HOENN_DATA by name, or None if not found.
def get_poke_dict_by_name(name):
    name_lower = name.lower()
    for pokemon in HOENN_DATA:
        if pokemon['Name'].lower() == name_lower:  # Compare names in lowercase
            return pokemon  # Return the Pokémon dictionary
    return None  # Return None if not found


# Display a list of Pokemon dicts, or a message if empty.
def display_pokemon_list(poke_list):
    if not poke_list:  # Check if the list is empty
        print("There are no Pokemons in this Pokedex that match the criteria.\n")
        return

    # Display each Pokemon
    for pokemon in poke_list:
        print_pokemon_by_id(pokemon['ID'])


########################
# 2) BST (By Owner Name)
########################

# Create and return a BST node dict with keys: 'owner', 'pokedex', 'left', 'right'.
def create_owner_node(owner_name, pokemon_id=None):
    # Create the new pokemon
    new_pokemon = get_poke_dict_by_id(pokemon_id)

    return {
        'owner': owner_name,
        'pokedex': [] if pokemon_id is None else [new_pokemon],
        'left': None,
        'right': None
    }


# Insert a new BST node by owner_name (alphabetically). Return updated root.
def insert_owner_bst(root, new_owner):
    # Base case: root can be inserted
    if root is None:
        return new_owner

    # Recursively search in the left or right subtree
    if new_owner['owner'].lower() < root['owner'].lower():
        root['left'] = insert_owner_bst(root['left'], new_owner)
    else:
        root['right'] = insert_owner_bst(root['right'], new_owner)

    return root


# Recursively locate a BST node by owner_name. Return that node or None if missing.
def find_owner_bst(root, owner_name):
    # Base case: Root is None or the owner name matches the current node
    if root is None:
        return None

    if root['owner'].lower() == owner_name.lower():
        return root

    # Recursively search in the left or right subtree
    if owner_name.lower() < root['owner'].lower():
        return find_owner_bst(root['left'], owner_name) # Go left
    else:
        return find_owner_bst(root['right'], owner_name) # Go Right


# Return the leftmost node in a BST subtree.
def min_node(node):
    while node is not None and node['left'] is not None:
        node = node['left']

    return node


# Remove a node from the BST by owner_name. Return updated root.
def delete_owner_bst(root, owner_name):
    # If the tree or subtree is empty
    if root is None:
        return None

    # Search for the root
    if owner_name < root['owner'].lower():
        root['left'] = delete_owner_bst(root['left'], owner_name)  # Go left
    elif owner_name > root['owner'].lower():
        root['right'] = delete_owner_bst(root['right'], owner_name)  # Go right

    else:  # found node to remove

        # Case 1: No children - a leaf
        if root['left'] is None and root['right'] is None:
            return None  # return None to remove this node

        # Case 2: One child
        if root['left'] is None:  # Only right child
            return root['right']  # Replace node with its right child

        elif root['right'] is None:  # Only left child
            return root['left']  # Replace node with its left child

        # Case 3: Two children: Get the in-order successor
        successor = min_node(root['right'])
        root['owner'] = successor['owner']
        root['pokedex'] = successor['pokedex']
        # Delete successor
        root['right'] = delete_owner_bst(root['right'], successor['owner'].lower())

    return root


########################
# 3) BST Traversals
########################

# BFS level-order traversal. Print each owner's name and # of pokemons.
def bfs_traversal(root):
    queue = [root]  # Initialize a queue with the root node

    while queue:
        # Remove and save the front node
        current_node = queue.pop(0)

        # Process the current node (print the owner's name + all pokemons)
        print(f"\nOwner: {current_node['owner']}\n")
        display_pokemon_list(current_node['pokedex'])

        # Add the left child to queue if it exists
        if current_node['left']:
            queue.append(current_node['left'])

        # Add the left child to queue if it exists
        if current_node['right']:
            queue.append(current_node['right'])


# Pre-order traversal (root -> left -> right). Print data for each node.
def pre_order(root):
    if root is None:
        return None

    # print owner name
    print(f"\nOwner: {root['owner']}\n")

    # print all owner's pokemons
    display_pokemon_list(root['pokedex'])

    pre_order(root['left'])  # Go left
    pre_order(root['right'])  # Go right


# In-order traversal (left -> root -> right). Print data for each node.
def in_order(root):
    if root is None:
        return None

    in_order(root['left'])  # Go left

    # print owner name
    print(f"\nOwner: {root['owner']}\n")
    # print all owner's pokemons
    display_pokemon_list(root['pokedex'])

    in_order(root['right'])  # Go right


# Post-order traversal (left -> right -> root). Print data for each node.
def post_order(root):
    if root is None:
        return None

    post_order(root['left'])  # Go left
    post_order(root['right'])  # Go right

    # print owner name
    print(f"\nOwner: {root['owner']}\n")
    # print all owner's pokemons
    display_pokemon_list(root['pokedex'])


########################
# 4) Pokedex Operations
########################

# Prints a pokemon by its id
def print_pokemon_by_id(pokemon_id):
    print(f"ID: {pokemon_id}, "
          f"Name: {HOENN_DATA[pokemon_id - 1]['Name']}, "
          f"Type: {HOENN_DATA[pokemon_id - 1]['Type']}, "
          f"HP: {HOENN_DATA[pokemon_id - 1]['HP']}, "
          f"Attack: {HOENN_DATA[pokemon_id - 1]['Attack']}, "
          f"Can Evolve: {HOENN_DATA[pokemon_id - 1]['Can Evolve']}")


# locate a pokemon from a list by its id. Return that id or None if missing.
def is_pokemon_in_pokedex_by_id(owner_node, pokemon_id):
    for pokemon in owner_node['pokedex']:
        if pokemon['ID'] == pokemon_id:
            return True
    return False


# locate a pokemon from a list by its name. Return his id or None if missing.
def is_pokemon_in_pokedex_by_name(owner_node, pokemon_name):
    name_lower = pokemon_name.lower()
    for pokemon in owner_node['pokedex']:
        if pokemon['Name'].lower() == name_lower:
            return True
    return False


# Prompt user for a Pokemon ID, find the data, and add to this owner's pokedex if not duplicate.
def add_pokemon_to_owner(owner_node):
    pokemon_id = read_int_safe("Enter Pokemon ID to add: ")

    # Check if the pokemon is already in the list
    if is_pokemon_in_pokedex_by_id(owner_node, pokemon_id):
        print("Pokemon already in the list. No changes made.\n")
        return

    # Create a copy of the pokemon
    poke_copy = get_poke_dict_by_id(pokemon_id)
    if poke_copy is None:
        return

    # Add the pokemon
    owner_node['pokedex'].append(poke_copy)

    # Print success
    print(f"Pokemon {HOENN_DATA[pokemon_id - 1]['Name']} (ID {pokemon_id}) "
          f"added to {owner_node['owner']}'s Pokedex.\n")


# Prompt user for a Pokemon name, remove it from this owner's pokedex if found.
def release_pokemon_by_name(owner_node):
    poke_name = input("Enter Pokemon Name to release: ")
    # Check if the pokemon is in the list
    poke_to_release = None

    for pokemon in owner_node['pokedex']:
        if pokemon['Name'].lower() == poke_name.lower():
            poke_to_release = pokemon
            break

    if not poke_to_release:
        print(f"No Pokemon named '{poke_name}' in {owner_node['owner']}'s Pokedex.\n")
        return

    owner_node['pokedex'].remove(poke_to_release)
    print(f"Releasing {poke_to_release['Name']} from {owner_node['owner']}.\n")

    return

# Evolve a Pokemon (ID -> ID+1) if allowed.
def evolve_pokemon_by_name(owner_node):
    poke_name = input("Enter Pokemon Name to evolve: ")
    # Check if the pokemon is in the list
    poke_to_evolve = None

    for pokemon in owner_node['pokedex']:
        if pokemon['Name'].lower() == poke_name.lower():
            poke_to_evolve = pokemon
            break

    if not poke_to_evolve:
        print(f"No Pokemon named '{poke_name}' in {owner_node['owner']}'s Pokedex.\n")
        return

    # Check if the pokemon can evolve
    if poke_to_evolve['Can Evolve'] == "FALSE":
        print(f"{poke_to_evolve['Name']} cannot evolve.\n")
        return

    # Make a copy of the evolved pokemon,
    # data base starts from 0 so poke_copy['ID'] like ID+1
    evolved_poke = get_poke_dict_by_name(HOENN_DATA[poke_to_evolve['ID']]['Name'])

    # Remove the old pokemon
    owner_node['pokedex'].remove(poke_to_evolve)

    # Check if the evolved pokemon is in the tree
    if evolved_poke not in owner_node['pokedex']:
        owner_node['pokedex'].append(evolved_poke)
        print(f"Pokemon evolved from {poke_to_evolve['Name']} (ID {poke_to_evolve['ID']}) to "
              f"{evolved_poke['Name']} (ID {evolved_poke['ID']}).\n")
        return

    # The evolved pokemon is already in the the list
    # Add the new pokemon
    owner_node['pokedex'].append(evolved_poke)
    # Remove it to not create duplicates
    owner_node['pokedex'].pop()

    # Print the corresponding message
    print(f"Pokemon evolved from {poke_to_evolve['Name']} (ID {poke_to_evolve['ID']}) to "
          f"{evolved_poke['Name']} (ID {evolved_poke['ID']}).\n"
          f"{evolved_poke['Name']} was already present; releasing it immediately.\n")  # success
    return


########################
# 5) Sorting Owners by # of Pokemon
########################

# Collect all BST nodes into a list (arr).
def gather_all_owners(root, owner_list):
    if root is None:
        return

    gather_all_owners(root['left'], owner_list)  # Go left
    gather_all_owners(root['right'], owner_list)  # Go right
    owner_list.append(root)


# Sort key, (#pokedex size, then alpha)
def sort_key(owner):
    return len(owner['pokedex']), owner['owner'].lower()


# Gather owners, sort them by (#pokedex size, then alpha), print results.
def sort_owners_by_num_pokemon(owner_list):
    # Sort the list
    owner_list.sort(key=sort_key)
    for owner in owner_list:
        print(f"Owner: {owner['owner']} (has {len(owner['pokedex'])} Pokemon)\n")


########################
# 6) Print All
########################

# Let user pick BFS, Pre, In, or Post. Print each owner's data/pokedex accordingly.
def print_all_owners():
    global ownerRoot
    if ownerRoot is None:
        print("No owners in the BST.\n")
        return

    print("1) BFS\n"
          "2) Pre-Order\n"
          "3) In-Order\n"
          "4) Post-Order\n")
    choice = read_int_safe("Your choice: ")

    if choice == 1:  # BFS
        bfs_traversal(ownerRoot)
    elif choice == 2:  # PRE ORDER
        pre_order(ownerRoot)
    elif choice == 3:  # IN ORDER
        in_order(ownerRoot)
    elif choice == 4:  # POST ORDER
        post_order(ownerRoot)
    else:
        print("Invalid choice.\n")


########################
# 7) The Display Filter Sub-Menu
########################

# Display a filter menu to show Pokémons based on user-defined criteria
def display_filter_sub_menu(owner_node):
    while True:
        print("\n-- Display Filter Menu --\n"
              "1. Only a certain Type\n"
              "2. Only Evolvable\n"
              "3. Only Attack above __\n"
              "4. Only HP above __\n"
              "5. Only names starting with letter(s)\n"
              "6. All of them!\n"
              "7. Back\n")

        choice = read_int_safe("Your choice: ")
        counter = 0
        if choice == 1:  # BY TYPE
            type_choice = input("Which Type? (e.g. GRASS, WATER): ").lower()
            counter = sum(print_pokemon_by_id(pokemon['ID']) or 1
                          for pokemon in owner_node['pokedex']
                          if pokemon['Type'].lower() == type_choice)

        elif choice == 2:  # ONLY EVOLVABLE
            counter = sum(print_pokemon_by_id(pokemon['ID']) or 1
                          for pokemon in owner_node['pokedex']
                          if pokemon['Can Evolve'] == "TRUE")

        elif choice == 3:  # ATTACK ABOVE
            attack_threshold = read_int_safe("Enter Attack threshold: ")
            counter = sum(print_pokemon_by_id(pokemon['ID']) or 1
                          for pokemon in owner_node['pokedex']
                          if pokemon['Attack'] >= attack_threshold)

        elif choice == 4:  # HP ABOVE
            hp_threshold = read_int_safe("Enter HP threshold: ")
            counter = sum(print_pokemon_by_id(pokemon['ID']) or 1
                          for pokemon in owner_node['pokedex']
                          if pokemon['HP'] >= hp_threshold)

        elif choice == 5:  # STARTING WITH
            starting_letters = input("Starting letter(s): ").lower()
            counter = sum(print_pokemon_by_id(pokemon['ID']) or 1
                          for pokemon in owner_node['pokedex']
                          if pokemon['Name'].lower().startswith(starting_letters))

        elif choice == 6:  # ALL POKEMONS
            display_pokemon_list(owner_node['pokedex'])
            continue

        elif choice == 7:  # BACK TO POKEDEX MENU
            print("Back to Pokedex Menu.\n")
            break

        else:
            print("Invalid choice.\n")
            continue

        if counter == 0:
            print("There are no Pokemons in this Pokedex that match the criteria.\n")


########################
# 8) Sub-menu & Main menu
########################

# Ask user for an owner name, locate the BST node, then show sub-menu
def existing_pokedex():
    owner_name = input("Owner name: ")
    # Check for duplicates
    cur_owner = find_owner_bst(ownerRoot, owner_name)
    if not cur_owner:
        print(f"Owner '{owner_name}' not found.\n")
        return

    else:
        while True:
            print(f"\n-- {cur_owner['owner']}'s Pokedex Menu --\n"
                  "1. Add Pokemon\n"
                  "2. Display Pokedex\n"
                  "3. Release Pokemon\n"
                  "4. Evolve Pokemon\n"
                  "5. Back to Main\n")
            sum_menu_choice = read_int_safe("Your choice: ")
            if sum_menu_choice == 1:  # ADD POKEMON
                add_pokemon_to_owner(cur_owner)
                continue

            elif sum_menu_choice == 2:  # DISPLAY POKEDEX
                display_filter_sub_menu(cur_owner)
                continue

            elif sum_menu_choice == 3:  # RELEASE POKEMON
                release_pokemon_by_name(cur_owner)
                continue

            elif sum_menu_choice == 4:  # EVOLVE POKEMON
                evolve_pokemon_by_name(cur_owner)
                continue

            elif sum_menu_choice == 5:  # BACK TO MAIN
                print("Back to Main Menu.\n")
                break

            else:
                print("Invalid choice.\n")
                continue

# Create a new owner with a new pokedox, if valid
def create_new_pokedex():
    global ownerRoot
    owner_name = input("Owner name: ")
    # Check for duplicates
    if find_owner_bst(ownerRoot, owner_name):
        print(f"Owner '{owner_name}' already exists. No new Pokedex created.\n")
        return

    # Get the first pokemon
    print("Choose your starter Pokemon:\n"
          "1) Treecko\n"
          "2) Torchic\n"
          "3) Mudkip\n")
    pokemon_id = read_int_safe("Your choice: ")

    if pokemon_id < 1 or pokemon_id > 3:  # Check if num is in range
        print("Invalid. No new Pokedex created.\n")
        return

    # Set the id based on the database
    if pokemon_id == 2:
        pokemon_id = 4
    elif pokemon_id == 3:
        pokemon_id = 7

    # Create a new owner node
    new_owner = create_owner_node(owner_name, pokemon_id)

    # Check if there are no previous owners
    if ownerRoot is None:
        ownerRoot = new_owner
        print(f"New Pokedex created for {owner_name} with starter "
              f"{HOENN_DATA[pokemon_id - 1]['Name']}.\n")
        return

    # Insert into the BST
    insert_owner_bst(ownerRoot, new_owner)

    print(f"New Pokedex created for {owner_name} with starter "
          f"{HOENN_DATA[pokemon_id - 1]['Name']}.\n")

# Print thw main menu, and get action from the user
def main_menu():
    global ownerRoot
    while True:
        print("\n=== Main Menu ===\n"
              "1. New Pokedex\n"
              "2. Existing Pokedex\n"
              "3. Delete a Pokedex\n"
              "4. Display owners by number of Pokemon\n"
              "5. Print All\n"
              "6. Exit\n")
        choice = read_int_safe("Your choice: ")

        if choice == 1:  # NEW POKEDEX
            create_new_pokedex()
            continue

        if choice == 2:  # EXISTING POKEDEX
            existing_pokedex()
            continue

        if choice == 3:  # DELETE POKEDEX
            owner_name = input("Enter owner to delete: ")
            # Check if owner exists, lower case too
            if not find_owner_bst(ownerRoot, owner_name):
                print(f"Owner '{owner_name}' not found.\n")
                continue

            print(f"Deleting {owner_name}'s entire Pokedex...\n")
            ownerRoot = delete_owner_bst(ownerRoot, owner_name.lower())  # Delete the pokedox
            print("Pokedex deleted.\n")
            continue

        if choice == 4:  # DISPLAY OWNERS BY NUMBER OF POKEMONS
            if ownerRoot is None:
                print("No owners at all.\n")
                continue

            owner_list = [] # Create owner list
            gather_all_owners(ownerRoot, owner_list)

            print("=== The Owners we have, sorted by number of Pokemons ===\n")
            sort_owners_by_num_pokemon(owner_list)  # Sort and print
            continue

        if choice == 5:  # PRINT OWNERS
            print_all_owners()
            continue

        if choice == 6:  # Exit
            print("Goodbye!\n")
            break

        else:
            print("Invalid choice.\n")

# Main func
def main():
    main_menu()


if __name__ == "__main__":
    main()
