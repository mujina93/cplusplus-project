// braggDumpv02
/* This function takes a pointer to a filled Event, and
    deallocates all the dynamicaly allocated memory associated
    with that Event.
    It deletes the dynamic array of measures of the event,
    and the pointed event itself (assuming it's dynamically allocated).
    If it just deleted the dynamic event, the dynamic array of its
    measures wouldn't be deleted.
*/

#include "Event.h"  // Event struct used

void clear(const Event* a_p_ev)
{
    // Deletes the dynamically allocated data (the energy array)
    delete[] a_p_ev->m_energies;

    // Deletes the dynamically allocated event itself
    delete a_p_ev;

    return;
}
