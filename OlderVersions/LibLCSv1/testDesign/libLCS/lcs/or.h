//////////////////////////////////////////////////////////////////////////////////
// This file is distributed as part of the libLCS library.
// libLCS is C++ Logic Circuit Simulation library.
//
// Copyright (c) 2006-2007, B. R. Siva Chandra
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// In case you would like to contact the author, use the following e-mail
// address: sivachandra_br@yahoo.com
//////////////////////////////////////////////////////////////////////////////////

#ifndef __LCS_OR_H__
#define __LCS_OR_H__

#include "module.h"
#include "bus.h"
#include "linestate.h"

namespace lcs
{ // Start of namespace lcs

/// A template class which encapsulates a logical OR gate. The first template parameter
/// \p width denotes the number of lines in the input data bus. In other words, the
/// template parameter \p width denotes the number of inputs to the OR gate. Hence,
/// one can instantiate an N-input OR gate by setting the template parameter value
/// to N. The second template parameter indicates the propogation delay from the input
/// to the output of the OR gate.
template <unsigned int width = 1, unsigned int delay = 0>
class Or : public Module
{
public:

    /// A constant integer which denotes the port id for the input port/bus.
    ///
    static const int INPUT;

    /// A constant integer which denotes the port id for the output bus/port.
    ///
    static const int OUTPUT;

public:

    /// The only meaningfull constructor for the class.
    /// A default constructor is not explicitly provided. Moreover, the one synthesized
    /// by the compiler is practically useless.
    ///
    /// \param output The single line output bus of the gate.
    /// \param input The multiline input bus to the gate.
    /// \param width The number of lines in the input bus.
    ///
    Or(const Bus<1> &output, const InputBus<width> &in1);

    /// Destructor.
    ///
    virtual ~Or();

    /// Propogates the input data line states to the output. This function is called
    /// by the input bus lines to notify the gate of a lcs::LINE_STATE_CHANGE event.
    /// When notified, an OR operation is performed on the line states of the data lines
    /// of the input bus and the result is propogated to the single line output bus.
    virtual void onStateChange(int portId);

private:
    Bus<1> outBus;
    InputBus<width> inBus;
};

template <unsigned int width, unsigned int delay> const int Or<width, delay>::INPUT   = 0;
template <unsigned int width, unsigned int delay> const int Or<width, delay>::OUTPUT  = 1;

template <unsigned int width, unsigned int delay>
Or<width, delay>::Or(const Bus<1>& output, const InputBus<width> &in)
                    : Module(), outBus(output), inBus(in)
{
    inBus.notify(this, LINE_STATE_CHANGE, INPUT);
    onStateChange(INPUT);
}

template <unsigned int width, unsigned int delay>
Or<width, delay>::~Or()
{
    inBus.stopNotification(this, LINE_STATE_CHANGE, INPUT);
}

template <unsigned int width, unsigned int delay>
void Or<width, delay>::onStateChange(int portId)
{
    for (unsigned int i = 0; i < width; i++)
    {
        if (inBus[i] == HIGH)
        {
            outBus[0] = (delay, HIGH);
            return;
        }
    }

    outBus[0] = (delay, LOW);
    return;
}

} // End of namespace lcs

#endif // __LCS_OR_H__
