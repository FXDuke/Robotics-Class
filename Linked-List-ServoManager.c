typedef struct ServoNode {
  struct ServoNode Next;
  Servo Current;
  int Index;
} Node;


typedef struct ServoTable {
  struct ServoNode Head;
  int Size;
  void (*pairs)(void (*)(int i, struct ServoNode v)); // Pairs
  int (*ins)(Servo Object); // Insert
  void (*del)(int Index); // Remove
}

struct ServoTable ServoManager;

void Pairs(void (*ReturnFunction)(int i, struct ServoNode v)) {
  struct ServoNode Current = ServoManager.Head;
  for (int Index=0;Index<=ServoManager.Size;Index++) {
    Current = Current->Next;
    ReturnFunction(Index,Current);
  }
}

int Ins(Servo Object) {
  struct ServoTable Last = ServoTable.Head;
  ServoManager.Head = (Node *) malloc(sizeof(Node));
  ServoManager * (*ServoManager.Size++) = ServoManager.Head;
  ServoManager.Head->Index = ServoManager.Size;
  ServoManager.Head->Current = Object;
  ServoManager.Head->Next = Last;
  return ServoManager.Size;
}


void Del(int Index) {
  struct ServoNode Current = ServoManager.Head;
  struct ServoNode Last;
  while (Current->Next != NULL) {
    if (Current.Index==Index) {
      stuct ServoNode _Current = Current->Next;
      for (int SizeIndex=Current.Index;SizeIndex<=ServoManager.Size;SizeIndex++) {
        if (_Current!=NULL) {
          ServoManager * (*SizeIndex) = _Current;
          _Current->Index = SizeIndex;
        }
      }
      ServoManager.Size--;
      Last->Next = Current->Next;
      free(Current);
      break;
    }
    Current = Current->Next;
    Last = Current;
  }
}

ServoManager.pairs = Pairs;
ServoManager.ins = Ins;
ServoManager.del = Del;
