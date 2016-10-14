#ifndef TQUEUE_H
#define TQUEUE_H

#include <TGlobal>
#include "thazardobject.h"
#include "thazardptr.h"
#include "tatomicptr.h"

namespace Tf
{
    static thread_local THazardPtr hzptrQueue;
}

template <class T> class TQueue
{
private:
    struct Node : public THazardObject
    {
        T value;
        TAtomicPtr<Node> next;
        Node(const T &v) : value(v) { }
    };

    TAtomicPtr<Node> queHead {nullptr};
    TAtomicPtr<Node> queTail {nullptr};
    std::atomic<int> counter {0};

public:
    TQueue();
    void enqueue(const T &val);
    bool dequeue(T &val);
    bool head(T &val);
    int count() const { return counter.load(std::memory_order_acquire); }

    T_DISABLE_COPY(TQueue)
    T_DISABLE_MOVE(TQueue)
};


template <class T>
inline TQueue<T>::TQueue()
{
    auto *dummy = new Node(T());  // dummy node
    queHead.store(dummy);
    queTail.store(dummy);
}


template <class T>
inline void TQueue<T>::enqueue(const T &val)
{
   auto *newnode = new Node(val);
   for (;;) {
        Node *tail = queTail.load();
        Node *next = tail->next.load();

        if (Q_UNLIKELY(tail != queTail.load())) {
            continue;
        }

        if (next) {
            queTail.compareExchangeStrong(tail, next);  // update queTail
            continue;
        }

        if (tail->next.compareExchange(next, newnode)) {
            counter++;
            queTail.compareExchangeStrong(tail, newnode);
            break;
        }
   }
}


template <class T>
inline bool TQueue<T>::dequeue(T &val)
{
    Node *next;
    for (;;) {
        Node *head = queHead.load();
        Node *tail = queTail.load();
        next = Tf::hzptrQueue.guard<Node>(&head->next);

        if (Q_UNLIKELY(head != queHead.load())) {
            continue;
        }

        if (head == tail) {
            if (!next) {
                // no item
                break;
            }
            queTail.compareExchangeStrong(tail, next);  // update queTail

        } else {
            if (!next) {
                continue;
            }

            val = next->value;
            if (queHead.compareExchange(head, next)) {
                head->deleteLater();  // gc
                counter--;
                break;
            }
        }
    }
    Tf::hzptrQueue.clear();
    return (bool)next;
}


template <class T>
inline bool TQueue<T>::head(T &val)
{
    Node *next;
    for (;;) {
        Node *headp = queHead.load();
        next = Tf::hzptrQueue.guard<Node>(&headp->next);

        if (Q_LIKELY(headp == queHead.load())) {
            if (next) {
                val = next->value;
            }
            break;
        }
    }
    Tf::hzptrQueue.clear();
    return (bool)next;
}

#endif // TQUEUE_H