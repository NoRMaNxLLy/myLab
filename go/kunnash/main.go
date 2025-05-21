package main

import (
	"fmt"
	"time"
)

type KnshDexEntry struct {
	id    string
	title string
	cdate time.Time
	mdate time.Time
}

func (E *KnshDexEntry) ID() (id string)           { return E.id }
func (E *KnshDexEntry) Title() (t string)         { return E.title }
func (E *KnshDexEntry) UpdateTitle(t string)      { E.title = t }
func (E *KnshDexEntry) UpateID(id string)         { E.id = id }
func (E *KnshDexEntry) UpdateModDate(d time.Time) { E.mdate = d }

type KnshDex []KnshDexEntry

func (D *KnshDex) ReadDexFile() {
	// read the index file into the slice
}

type Knsh struct {
	Dex  KnshDex
	next []*Knsh
}

func (k *Knsh) Titles() (t []string) {
	for _, E := range k.Dex {
		t = append(t, E.ID()+"\t"+E.Title())
	}

	return t
}

func main() {
	knsh := &Knsh{
		Dex: KnshDex{
			{},
			{"1", "# testing", time.Now(), time.Now()},
			{"2", "# testing again", time.Now(), time.Now()},
		},
		next: nil,
	}

	titles := knsh.Titles()

	for _, t := range titles {
		fmt.Println(t)
	}

}
