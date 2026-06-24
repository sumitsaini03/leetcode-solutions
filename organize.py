import os
import shutil

# Keywords -> Folder
topic_map = {
    "tree": "Trees",
    "binary-tree": "Trees",
    "bst": "BST",
    "graph": "Graphs",
    "array": "Arrays",
    "string": "Strings",
    "linked-list": "LinkedList",
    "stack": "Stack",
    "queue": "Queue",
    "heap": "Heap",
    "trie": "Tries",
    "binary-search": "BinarySearch",
    "backtracking": "Backtracking",
    "greedy": "Greedy",
    "dynamic-programming": "DynamicProgramming",
    "bit-manipulation": "BitManipulation"
}

for item in os.listdir():
    if os.path.isdir(item):
        lower_name = item.lower()

        for key, folder in topic_map.items():
            if key in lower_name:
                destination = os.path.join(folder, item)

                if not os.path.exists(destination):
                    shutil.move(item, destination)
                    print(f"Moved {item} -> {folder}")
                break