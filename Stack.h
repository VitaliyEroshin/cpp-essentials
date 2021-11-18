class Stack {
  struct Node {
    int value;
    Node* previous;
  };

  int _size = 0;
  Node* head = nullptr;

  public:
    void push(int x);

    int back() { return head->value; }

    int pop();

    void clear();

    int size() { return _size; }
};

void Stack::push(int x) {
  Node* node = new Node();
  node->previous = head;
  node->value = x;
  head = node;
  _size++;
}

int Stack::pop() {
  int return_value = back();
  Node* new_head = head->previous;
  delete head;
  head = new_head;
  _size--;
  return return_value;
}

void Stack::clear() {
  Node* new_head;
  while (head != nullptr) {
    new_head = head->previous;
    delete head;
    head = new_head;
  }
  _size = 0;
}