from lab12.boyer_moore import bm_search

TEXT1 = """Clash Royale is a free-to-play video game (afree-to-play)"""
SEARCH_PATTERN_1 = "afree-to-play"

TEXT_2 = "cabcbbbcabca"
SEARCH_PATTERN_2 = "cabca"


def get_minmax_word(text_to_process: str):
    text = text_to_process.split()

    return min(text, key=len) + max(text, key=len)


if __name__ == "__main__":
    text = TEXT1
    search_pattern = get_minmax_word(text)
    bm_search(text, search_pattern)
    print()
