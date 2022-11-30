"""
Match suffix and prefix on every iteration
If is the same, start from the point, where prefix was placed (before incorrect character)

Algorithm:
1) i and j are two pointers
2) j moves only j==i (j++, i++), in this case comp[i] = j + 1
3) i moves every time, comp[i] = 0 if not matched with comp[j]
"""

# wikipedia sentence

from lab11.kmp_search import kmp_search

TEXT_1 = "ab abab"  # ababab
TEXT_2 = "ababacadababab"


def get_minmax_word(text_to_process: str):
    text = text_to_process.split()

    return min(text, key=len) + max(text, key=len)


if __name__ == "__main__":
    search_pattern = get_minmax_word(TEXT_1)
    kmp_search(TEXT_2, search_pattern)
