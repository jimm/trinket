# Trinket

Trinket is MIDI performance software. It allows a musician to create and
modify MIDI data in real time.

For more information see the [wiki](https://github.com/jimm/trinket/wiki). \[TODO\]

# Pipes

Most pipes take MIDI input from some pipe, do something to it, and output it
to another pipe.

Some pipes generate MIDI data, so they don't have an input. Some pipes
output MIDI data to a PortMidi port, so they don't have an output to any
other pipe.

## Input

Gets its input from a PortMidi port.

## Output

Sends its input to a PortMidi output.

## Fan

Copies its input to one or more pipes. This is the only pipe that has
multiple outputs.

## Transpose

If the incoming message is a note message (note on, note off, or polyphonic
pressure), it transposes the note number by a specified amount.

All other messages are passed through unchanged.

## Range

If the incoming message is a note message (note on, note off, or polyphonic
pressure), it passes them through only if they are within the specified low
and high notes. Note messages that are lower or higher are dropped.

All other messages are passed through unchanged.

## Channel Remap

Remaps MIDI channels. Any channel can be remapped to another or filtered
out.

## Transform

Transforms one kind of MIDI message into another.

### Source Message Types

- Note on value
- Note on velocity
- Controller
- Program change
- Channel pressure
- Start, continue, stop

### Destination Message Types

- Controller
- Program change
- Channel pressure
- Start, continue, stop

TODO: write about how the more odd mappings, like start -> controller, are handled.

# To Do / Bugs

See the [To Do](https://github.com/jimm/trinket/wiki/To-Do) list on the
Wiki.
