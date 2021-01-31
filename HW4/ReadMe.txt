	# Ana menu

   "=========================="    	# Ana menu   
<< " ====== MAIN MENU =======" 	
<< "1-Create a new game " 		# Ana menude 4 farkli islem yapabiliyoruz	
<< "2-Play an existing game" 		
<< "3-Compare two game" 		# Karsilastirmak isterseniz size mevcut oyunlari 						# listeleyecek  ve 2 oyun ismi isteyecek
<< "4-Quit" 

# 1-> Sizden her oyun icin fakli bir id isteniyor ve oyun olusturulup maindeki oyunlar listesine konuyor
# 2-> Olusturdugumuz oyunlardan hangisini oynamak istiyorsak id'sini girip oynuyoruz
# 3-> Game listesindeki 2 id girmenizi istiyor ve karsilastiriyor
# 4-> Programi kapatiyor


# ust kisimda oyun listesi sergileniyor
Existing game names :
Game 1 :orngame
Game 2 :game1
Game 3 :game2
Game 4 :game3
Game 5 :game4
----------------------
Filled Cells Of All Games : 18		#Dolu olan cell static degeri


//////////////////////////////////////////////////////////////////////////////////////////////

	#Oyun Komutlari

 \"SAVE file.txt\"      # mevcut oyunu kaydediyor
 \"LOAD file.txt\"      # var olan bir oyunu yukluyor
 \"--\"                 # (*this)--
 \"---\"                # --(*this)
 \"SIZE\"               # boardi tekrardan resize etmeyi saglar 
 \"MENU\"               # ana menuye dondurur

# eger yanlis bir komut girerseniz veya uygun olmayan bir kordinat sizi farkli bir fonksiyona gonerip sadece kordinat girmeniz isteniyor


//////////////////////////////////////////////////////////////////////////////////////////////

#ornek oyun ici cikti

ID   : orngame   Size : 8   Type : 1   Turn : 12   Winner: .   finish :0
Score of User 1(x): 4
Score of User 2(o): 5

  A B C D E F G H 
1 . x . o . . . . 
2  . x x o x . . . 
3   x o x o . . . . 
4    . . o o . . . . 
5     . . . . . . . . 
6      . . . . . . . . 
7       . . . . . . . . 
8        . . . . . . . . 
=====================================
Player x
Enter coordinate :(ex: A 5) :







