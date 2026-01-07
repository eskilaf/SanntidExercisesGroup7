package main

import (
	"fmt"
	"time"
)

func producer(chan1 chan int) {

	for i := 0; i < 10; i++ {
		time.Sleep(100 * time.Millisecond)
		fmt.Printf("[producer]: pushing %d\n", i)
		// TODO: push real value to buffer
		chan1 <- i
	}

}

func consumer(chan1 chan int) {

	time.Sleep(1 * time.Second)
	for {
		i := <-chan1 //TODO: get real value from buffer
		fmt.Printf("[consumer]: %d\n", i)
		time.Sleep(50 * time.Millisecond)
	}

}

func main() {

	// TODO: make a bounded buffer
	chan1 := make(chan int, 5)

	go consumer(chan1)
	go producer(chan1)

	select {}
}
