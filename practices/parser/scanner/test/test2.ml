 signature QUEUE = 
 sig
    type 'a queue
    exception QueueError
    val empty     : 'a queue
    val isEmpty   : 'a queue -> bool
    val singleton : 'a -> 'a queue
    val insert    : 'a * 'a queue -> 'a queue
    val peek      : 'a queue -> 'a
    val remove    : 'a queue -> 'a * 'a queue
 end
