class Queue:
    def __init__(self):
        self.items = []

    # Add an element
    def enqueue(self, item):
        self.items.append(item)

    # Remove an element
    def dequeue(self):
        if len(self.items) < 1:
            return None
        return self.items.pop(0)

    # Merge queues
    def merge(self, other_queue):
        self.items = self.items + list(set(other_queue.items) - set(self.items))
        return self

    def __len__(self):
        return len(self.items)
