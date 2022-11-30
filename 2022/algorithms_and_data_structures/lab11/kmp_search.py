import time


def kmp_search(text, search_pattern):
    start_time = time.time()
    arr = _init_preprocessed(search_pattern)
    print(f"Preprocessed prefix-suffix array: {arr}\n")
    has_found = _kmp_search(arr, search_pattern, text)
    if has_found:
        print(f"Found '{search_pattern}'")
    else:
        print(f"'{search_pattern}' not found")
    print("Time took: %s seconds" % (time.time() - start_time))


def _init_preprocessed(w):
    arr = [0] * len(w)
    m = len(w)
    i = 0
    j = 1

    # No proper prefix for string of length 1:
    arr[0] = 0

    while j < m:
        if w[i] == w[j]:
            i += 1
            arr[j] = i
            j += 1

        # The first character didn't match:
        elif i == 0:
            arr[j] = 0
            j += 1

        # Mismatch after at least one matching character:
        else:
            i = arr[i - 1]

    return arr


def _kmp_search(preprocessed_arr, pattern, text):
    # Initialising variables:
    i = 0
    j = 0
    m = len(pattern)
    n = len(text)

    # Start search:
    while i < m and j < n:
        pattern_display = ["-"] * m
        text_display = ["-"] * n
        text_display[j] = "x"
        print(f"Checking text={j}, pattern={i}:")
        print(f"{text}\n{''.join(text_display)}")

        if pattern[i] == text[j] and i == m - 1:
            # Last character matches -> Substring found:
            return True
        elif pattern[i] == text[j]:
            pattern_display[i] = "x"
            print(f"matched:\n{pattern}\n{''.join(pattern_display)}")
            i += 1
            j += 1
        else:
            # Character didn't match -> Backtrack:
            print("not matched, go back:")
            if i != 0:
                i = preprocessed_arr[i - 1]
            else:
                j += 1
            pattern_display[i] = "x"
            print(f"{pattern}\n{''.join(pattern_display)}")
        print()

    # Substring not found:
    return False
