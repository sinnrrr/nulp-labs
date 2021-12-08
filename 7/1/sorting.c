void swap(long array[], long pos1, long pos2) {
    long tmp;
    tmp = array[pos1];
    array[pos1] = array[pos2];
    array[pos2] = tmp;
}

void qsSort(long array[], long start, long end) {
    long head = start, tail = end - 1;
    long diff = end - start;
    long peIndex;
    // якщо залишилося менше двох елементів – кінець рекурсії
    if (diff < 1)
        return;
    if (diff == 1)
        if (array[start] > array[end]) {
            swap(array, start, end);
            return;
        }
    // пошук індексу розділяючого елементу peIndex
    long m = (start + end) / 2;
    if (array[start] <= array[m]) {
        if (array[m] <= array[end])
            peIndex = m;
        else if (array[end] <= array[start])
            peIndex = start;
        else
            peIndex = end;
    } else {
        if (array[start] <= array[end])
            peIndex = start;
        else if (array[end] <= array[m])
            peIndex = m;
        else
            peIndex = end;
    }
    long pe = array[peIndex]; // сам розділяючий елемент
    swap(array, peIndex, end);

    while (1) {
        while (array[head] < pe)
            ++head;
        while (array[tail] > pe && tail > start)
            --tail;
        if (head >= tail)
            break;
        swap(array, head++, tail--);
    }
    swap(array, head, end);
    long mid = head;
    qsSort(array, start, mid - 1); // рекурсивний виклик для 1-ої підмножини
    qsSort(array, mid + 1, end);   // рекурсивний виклик для 2-ої підмножини
}

void insertionSort(long n, long mass[]) {
    long newElement, location;

    for (long i = 1; i < n; i++) {
        newElement = mass[i];
        location = i - 1;

        while (location >= 0 && mass[location] > newElement) {
            mass[location + 1] = mass[location];
            location = location - 1;
        }

        mass[location + 1] = newElement;
    }
}
