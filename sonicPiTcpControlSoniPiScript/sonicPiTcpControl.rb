#s = TCPSocket.new 'localhost', 2016 #create socket
#s = TCPSocket.open('localhost', 2016)

note = 50
s = TCPSocket.open('localhost', 2016)

sleep 1

pageList = Array.new(10)

live_loop :tcp do
  
  receivedMessage = s.recv(50)
  
  puts receivedMessage
  
  if receivedMessage.include? ";"
    
    puts "contains ;"
    
    singleMessagesArray = receivedMessage.split(";")
    
    for singleMessage in singleMessagesArray do
        
        
      end
      
      
      puts singleMessagesArray
      
    end
    
    
    
    puts "note: "
    puts note
    #end
    #cue :p if k !=0 # if value is not 0 cue play loop
    
    #puts "close socket"
    
    sleep 1
  end
  
  
  
  
  #puts "close socket"
  #s.close #close =socket
  
  live_loop :x do #loop to play the notes
    play note
    puts "play note: "
    puts note
    sleep 8.2 #short sleep
    
  end