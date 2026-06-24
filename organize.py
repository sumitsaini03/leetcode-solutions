import os
import shutil

topics = {
    "two-sum": "Arrays",
    "maximum-depth-of-binary-tree": "Trees",
    "same-tree": "Trees",
    "reverse-linked-list": "LinkedList",
    "merge-two-sorted-lists": "LinkedList",
    "valid-parentheses": "Stack",
    "binary-search": "BinarySearch",
}

for item in os.listdir():
    if os.path.isdir(item):
        name = item.lower()

        for problem, topic in topics.items():
            if problem in name:
                destination = os.path.join(topic, item)

                if not os.path.exists(destination):
                    shutil.move(item, destination)
                    print(f"Moved {item} -> {topic}")