#include <stdio.h>
#include "src/fat.h"
#include "string.h"


int main () {
	//char nomToFind[] = "first";
	char nom[] = "second";
	unsigned short auteur = 7;
	//char data[] ="Hello, everyone! This is one of the weirdest sites: or your money back! We have ZIM, neopets, music, and much, much, more. E-mail us for questions, comments, complaints and information. Why not click on the Very Weird Stuff link to see more, or click on the music link? We have halloween and christmas pictures on the NeoPics link. Cheese is not a wild thing!!!!!!!!! Now I have decided to go for a world record. I will try to make the longest web page ever, made completely out of text! Won't that be fun? I will just type, and type, and never, ever use copy and paste. Wow...I really must be bored. Just goes to show what boredom can do to you. Any way, that's it for now. Wait, no it isn't, I still have to keep going, and going, and going. Because I do. THE REST OF THE STUFF I TYPE WILL BE COMPLETLY IN CAPS JUST BECAUSE I CAN. THAT IS ALL. SEEYA! Hi, I'm back. So far this is nowhere near the world record. I think. I don't exactly know where it is...oh, well. I'll just have to do the very best that I can. No one is really coming here, anyway. So it doesn't matter. By the way, TAB is a worthwhile, community-service organization. The form link is to a 100% fake TAB registration form that you can fill out just for laughs. I can't believe I'm bothering to do this. I have very low expectations of my site. None ever comes here, I could do this all day long and I still wouldn't have any more hits. This is just a pointless excursive in spelling errors and grammatical imprecision. May your day be shiney! The following is an extremely weird poem-thingy that I wrote when I was in a relatively weird mood:never mind that noise my dear can anyone pass the cheese only if you say pretty please oh, boy do I have to sneeze. why must everyone always rhyme, why I’m a poet and don’t I know it? what I fear comes right after here not this life or the next will I ever be able to pass the test? we’re stuck in here, (alone my dear) and we’ll problem never get out so don’t start to shout. it’s dark and I want to go home is where the heart was where is it now? we’ll never know but oh crap it’s starting to snow and it’s time to show and tell about the well that y";
	char data[] = "bonjouree";
	unsigned int taille = sizeof(data);
	char *readData;

	struct objet *objTemp;


	initialise_fat();
	addNewObject(nom, auteur, taille, data);
	objTemp = rechercher_objet("second");


	printObject(objTemp);

	objTemp = rechercher_objet("first");

	printObject(objTemp);
	objTemp = rechercher_objet(nom);
	readObject(objTemp, &readData);
	//supprimer_objet(nom);

//	printObject(objTemp);

//	objTemp = rechercher_objet("first");
//	printObject(objTemp);


	printf("%s\n", readData);
	supprimer_tout();
	free(readData);
	return 0;
}
