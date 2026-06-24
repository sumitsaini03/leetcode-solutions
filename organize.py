import os
import shutil
import requests

query = """
query getQuestionDetail($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    topicTags {
      slug
    }
  }
}
"""

topic_map = {
    "array": "Arrays",
    "string": "Strings",
    "hash-table": "Hashing",
    "linked-list": "LinkedList",
    "stack": "Stack",
    "queue": "Queue",
    "binary-search": "BinarySearch",
    "tree": "Trees",
    "binary-search-tree": "BST",
    "heap": "Heap",
    "graph": "Graphs",
    "greedy": "Greedy",
    "backtracking": "Backtracking",
    "dynamic-programming": "DynamicProgramming",
    "bit-manipulation": "BitManipulation",
    "trie": "Tries"
}

for folder in os.listdir():
    if not os.path.isdir(folder):
        continue

    if folder in topic_map.values():
        continue

    slug = folder.split("-",1)[-1]

    try:
        response = requests.post(
            "https://leetcode.com/graphql",
            json={
                "query": query,
                "variables": {"titleSlug": slug}
            }
        )

        tags = response.json()["data"]["question"]["topicTags"]

        if not tags:
            continue

        tag = tags[0]["slug"]

        if tag in topic_map:
            destination = os.path.join(topic_map[tag], folder)

            if not os.path.exists(destination):
                shutil.move(folder, destination)
                print(folder, "->", topic_map[tag])

    except:
        pass