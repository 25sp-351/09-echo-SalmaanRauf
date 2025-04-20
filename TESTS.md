# Test Case 1: single connection – basic line echo  
**Steps:**  
Start the server:  

./echo_server -v  

In another terminal, connect with:  

'telnet localhost 2345'  

Type:  
```
hello
```

=== Expected Program Output ===  
hello  
====================  
Result: PASS  

---

# Test Case 2: concurrent connections – each sees own output  
**Steps:**  
With server running, open **two** terminal tabs and run:  
```
telnet localhost 2345  
```  
In Tab 1 type:  
```
abcd
```

In Tab 2 type:  
```
efgh
```

=== Expected Program Output ===  
Each tab sees **only its own messages** echoed back.  
Server console prints both lines without overlap.  
====================  
Result: PASS  

---

# Test Case 3: server prints input when -v is enabled  
**Steps:**  
Run server with:  
```
./echo_server -v  
```  
From a telnet tab, type:  
```
chicken
```

=== Expected Program Output ===  
Server console prints:  
```
chicken
```  
Telnet session also echoes:  
```
chicken
```  
====================  
Result: PASS  

---

# Test Case 4: no -v flag – server should stay silent  
**Steps:**  
Run server with:  
```
./echo_server  
```  
Connect via telnet and type:  
```
quiet
```

=== Expected Program Output ===  
Telnet session shows:  
```
quiet
```  
Server terminal prints **nothing**.  
====================  
Result: PASS  

---

# Test Case 5: server handles long words + multiple newlines  
**Steps:**  
In a telnet session, type multiple lines quickly:  
```
apples
bananas
carrots
```

=== Expected Program Output ===  
Each line is echoed back immediately after pressing Enter.  
Server prints all lines (if -v is set) without truncation or error.  
====================  
Result: PASS  

