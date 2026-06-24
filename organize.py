import os
import shutil
import json
import urllib.request

# GraphQL query to fetch topic tags for a LeetCode problem by its title slug
QUERY = """
query getQuestionDetail($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    topicTags {
      slug
    }
  }
}
"""

# Map LeetCode topic slugs to local folder names
TOPIC_MAP = {
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
    "trie": "Tries",
}


def fetch_tags(slug):
    """Fetch topic tags for a LeetCode problem using its title slug.

    Uses the standard library `urllib` so the script works on any Python
    install without extra dependencies. Returns a list of tag slugs, or
    None if the request failed or the problem wasn't found.
    """
    payload = json.dumps({
        "query": QUERY,
        "variables": {"titleSlug": slug},
    }).encode("utf-8")

    req = urllib.request.Request(
        "https://leetcode.com/graphql",
        data=payload,
        headers={
            "Content-Type": "application/json",
            "User-Agent": "leetcode-organizer/1.0",
        },
        method="POST",
    )

    try:
        with urllib.request.urlopen(req, timeout=15) as resp:
            body = resp.read().decode("utf-8")
    except Exception as e:
        print(f"  network error for {slug}: {e}")
        return None

    try:
        data = json.loads(body)
    except json.JSONDecodeError as e:
        print(f"  invalid JSON for {slug}: {e}")
        return None

    question = data.get("data", {}).get("question")
    if not question:
        return None

    return [t["slug"] for t in question.get("topicTags", [])]


def main():
    existing_topic_dirs = set(TOPIC_MAP.values())
    moved = 0
    skipped = 0

    for entry in os.listdir():
        if not os.path.isdir(entry):
            continue
        if entry in existing_topic_dirs:
            continue

        slug = entry.split("-", 1)[-1]
        print(f"Checking: {entry} (slug={slug})")

        tags = fetch_tags(slug)
        if not tags:
            print(f"  no tags, skipping")
            skipped += 1
            continue

        for tag in tags:
            if tag in TOPIC_MAP:
                destination = os.path.join(TOPIC_MAP[tag], entry)
                if not os.path.exists(destination):
                    shutil.move(entry, destination)
                    print(f"  moved: {entry} -> {TOPIC_MAP[tag]}")
                    moved += 1
                break
        else:
            print(f"  no matching topic for tags {tags}, skipping")
            skipped += 1

    print(f"\nDone. Moved {moved} folder(s), skipped {skipped}.")


if __name__ == "__main__":
    main()
