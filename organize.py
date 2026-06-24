import os
import shutil
import json
import urllib.request

QUERY = """
query getQuestionDetail($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    topicTags {
      slug
    }
  }
}
"""

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
    "two-pointers": "TwoPointers",
    "sliding-window": "SlidingWindow",
    "depth-first-search": "Trees",
    "breadth-first-search": "Trees",
    "recursion": "Backtracking",
    "divide-and-conquer": "DynamicProgramming",
    "sorting": "Arrays",
    "matrix": "Arrays",
}

SKIP_DIRS = {
    ".github", ".vscode", "__pycache__", ".git", "node_modules",
}


def fetch_tags(slug):
    # Option 1: public mirror
    try:
        url = f"https://alfa-leetcode-api.onrender.com/select?titleSlug={slug}"
        req = urllib.request.Request(url, headers={"User-Agent": "leetcode-organizer/1.0"})
        with urllib.request.urlopen(req, timeout=15) as resp:
            data = json.loads(resp.read().decode("utf-8"))
            tags = data.get("topicTags", [])
            if tags:
                return [t["slug"] for t in tags]
    except Exception as e:
        print(f"  mirror failed: {e}")

    # Option 2: official GraphQL fallback
    payload = json.dumps({
        "query": QUERY,
        "variables": {"titleSlug": slug},
    }).encode("utf-8")
    req = urllib.request.Request(
        "https://leetcode.com/graphql",
        data=payload,
        headers={
            "Content-Type": "application/json",
            "User-Agent": "Mozilla/5.0",
            "Referer": "https://leetcode.com",
        },
        method="POST",
    )
    try:
        with urllib.request.urlopen(req, timeout=15) as resp:
            data = json.loads(resp.read().decode("utf-8"))
            question = data.get("data", {}).get("question")
            if question:
                return [t["slug"] for t in question.get("topicTags", [])]
    except Exception as e:
        print(f"  graphql error for {slug}: {e}")

    return None


def parse_slug(folder_name):
    parts = folder_name.split("-", 1)
    if len(parts) == 2 and parts[0].isdigit():
        return parts[1]
    return folder_name


def find_problem_folders(root):
    """
    Yield (absolute_path, folder_name) for every problem folder.
    Problem folders start with a number: '104-maximum-depth-...'
    Searches root AND one level of known subfolders like 'leetcode-solutions/'.
    """
    existing_topic_dirs = set(TOPIC_MAP.values())

    search_dirs = [root]

    # Also search inside 'leetcode-solutions/' subfolder if it exists
    leetcode_sub = os.path.join(root, "leetcode-solutions")
    if os.path.isdir(leetcode_sub):
        search_dirs.append(leetcode_sub)

    for search_dir in search_dirs:
        for entry in sorted(os.listdir(search_dir)):
            full_path = os.path.join(search_dir, entry)
            if not os.path.isdir(full_path):
                continue
            if entry in existing_topic_dirs:
                continue
            if entry in SKIP_DIRS or entry.startswith("."):
                continue
            # Must start with a digit (LeetHub naming: '104-maximum-...')
            if entry[0].isdigit():
                yield full_path, entry


def main():
    root = os.path.dirname(os.path.abspath(__file__))  # always relative to script
    existing_topic_dirs = set(TOPIC_MAP.values())
    moved = 0
    skipped = 0

    for full_path, entry in find_problem_folders(root):
        slug = parse_slug(entry)
        print(f"Checking: {entry} (slug={slug})")

        tags = fetch_tags(slug)
        if not tags:
            print(f"  no tags found, skipping")
            skipped += 1
            continue

        print(f"  tags: {tags}")

        for tag in tags:
            if tag in TOPIC_MAP:
                dest_dir = os.path.join(root, TOPIC_MAP[tag])
                os.makedirs(dest_dir, exist_ok=True)
                destination = os.path.join(dest_dir, entry)
                if not os.path.exists(destination):
                    shutil.move(full_path, destination)
                    print(f"  ✓ moved: {entry} → {TOPIC_MAP[tag]}/")
                    moved += 1
                else:
                    print(f"  already exists at {destination}, skipping")
                    skipped += 1
                break
        else:
            print(f"  no matching topic for tags {tags}, skipping")
            skipped += 1

    print(f"\nDone. Moved {moved} folder(s), skipped {skipped}.")


if __name__ == "__main__":
    main()