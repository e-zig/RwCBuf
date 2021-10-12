#include <iostream>
#include <limits>

#include "RwCBuf.hpp"


// ===== Alias of testing buffer ========
using RwCBufType = RwCBuf<10, int>;  // =
// ======================================

using namespace std;

// Help function
void clearCin() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Uncomment for heap allocate variant
//#define DYNBUF

int main() {
#ifdef DYNBUF
  RwCBufType* pbuf = new (RwCBufType);
#else
  RwCBufType buf;
  RwCBufType* pbuf{&buf};
#endif

  RwCBufType::value_type c;
  RwCBufType::size_type in;

  cout << "Buffer length: " << pbuf->size << endl;
  cout << "Type of buffer items: " << typeid(c).name() << endl;

  //================== Test cycle =======================
  do {
    cout << "Set ReWrite mode (1 - on, 0 - off, >1 - exit): ";

    // Reset and set mode
    if ((cin >> in).good()) {
      if (in == 1) pbuf->reset(RwCBufType::rwType::rwBuf);
      if (in == 0) pbuf->reset(RwCBufType::rwType::nonRwBuf);
      if (in > 1) break;
    } else
      pbuf->reset(RwCBufType::rwType::rwBuf);

    cout << "Buffer reset in ";

    if (bool(pbuf->reWriteMode()))
      cout << "ReWrite mode" << endl;
    else
      cout << "Non-ReWrite mode" << endl;

    cout << "Enter items into the buffer (separated by space):" << endl;

    clearCin();

    // Read console and write items by operator <<
    do {
      if ((cin >> c).good())
        *pbuf << c;
      else
        break;

      if ((cin.peek() != '\n') && (cin.peek() != ' ')) cin.get();

      while (cin.peek() == ' ') cin.get();

    } while (cin.peek() != '\n');

    clearCin();

    // Check full flag
    if (pbuf->isFull()) cout << "Buffer is full" << endl;

    // Check that an overwrite has occurred
    if (pbuf->isOverwritten()) cout << "Items in buffer overwritten" << endl;

    cout << "Buffer has " << pbuf->count() << " items: ";

    // Read (not extract) items by direct access to buffer array
    if (pbuf->count() > 0) {
      for (RwCBufType::size_type i = 0; i < pbuf->count(); ++i)
        cout << (*pbuf)[i] << " ";
      cout << endl;
    }

    // Extract items by operator >>
    while (!pbuf->isEmpty()) {
      cout << endl << "Number of items to read: ";
      if ((cin >> in).good()) {
        if (in > 0)
          for (auto k = 0; k < in; ++k) {
            if (pbuf->isEmpty()) break;
            *pbuf >> c;
            cout << c << " ";
          }
      } else
        clearCin();
    }

    if (pbuf->isEmpty()) cout << endl << "Buffer is empty" << endl;

    cout << endl << "===================================" << endl;

  } while (true);
  //================== End of Test cycle =======================

#ifdef DYNBUF
  delete pbuf;
#endif

  return 0;
}
