// Use `go run foo.go` to run your program

package main

import (
	"fmt"
	"runtime"
	"sync"
	"time"
)

var (
	i  = 0
	mu sync.Mutex
)

type operation struct {
	operationType string
	channel       chan int
}

func mainroutine(ops <-chan operation) {
	var counter int
	for op := range ops {
		switch op.operationType {
		case "inc":
			counter++
		case "dec":
			counter--
		case "get":
			op.channel <- counter
		}
	}
}

func main() {
	// What does GOMAXPROCS do? What happens if you set it to 1?
	runtime.GOMAXPROCS(2)
	//TODO: decrement i 1000000 times
	ops := make(chan operation)
	go mainroutine(ops)

	var wg sync.WaitGroup

	/*
		for j := 0; j < 999998; j++ {
			wg.Add(1)
			go func() {
				ops <- operation{operationType: "dec"}
				wg.Done()
			}()
		}
		for j := 0; j < 1000000; j++ {
			wg.Add(1)
			go func() {
				ops <- operation{operationType: "inc"}
				wg.Done()
			}()
		}
	*/

	wg.Add(2)
	
	go func() {
		for j := 0; j < 99; j++ {
			ops <- operation{operationType: "dec"}
			fmt.Println("type = dec")
		}

		wg.Done()
	}()

	go func() {
		for j := 0; j < 100; j++ {
			ops <- operation{operationType: "inc"}
			fmt.Println("type = inc")
		}

		wg.Done()
	}()

	wg.Wait()

	response := make(chan int)
	ops <- operation{operationType: "get", channel: response}

	// We have no direct way to wait for the completion of a goroutine (without additional synchronization of some sort)
	// We will do it properly with channels soon. For now: Sleep.
	time.Sleep(500 * time.Millisecond)
	fmt.Println("The magic number is:", <-response)
}