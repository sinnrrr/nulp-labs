import random

from lab9.rb_tree import RedBlackTree


def gen_random_real_array(n):
    return random.sample(range(-1000, 1000), n)


# Варіант 7: N, M – цілі;
# третій за значенням по зростанню елемент та його колір;
# чи є елемент у дереві та його колір.


if __name__ == "__main__":
    print()
    N = int(input("Enter number N: ") or 10)
    print()

    bst = RedBlackTree()
    arr = gen_random_real_array(N)

    for x in range(N):
        bst.insert(x)
        print(f"Inserted: {x}")
    print()

    print("Resulting tree")
    bst.print_tree()
    print()

    while True:
        M = float(input("Please enter value to search: ") or 10.0)
        v = bst.search_tree(M)

        if v == bst.TNULL:
            print("Not found")
            print()
            continue

        print(f"Found: {v.item} ({bst.get_node_color(v)})")

        if not v.parent or v.parent == bst.TNULL:
            print("No parent node")
        else:
            print(f"Parent: {v.parent.item} ({bst.get_node_color(v.parent)})")

        if not v.left or v.left == bst.TNULL:
            print("No left node")
        else:
            print(f"Left node: {v.left.item} ({bst.get_node_color(v.left)})")

        if not v.right or v.right == bst.TNULL:
            print("No right node")
        else:
            print(f"Right node: {v.right.item} ({bst.get_node_color(v.right)})")

        print()
