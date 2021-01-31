Oyun iki ana menu uzerinden donuyor  :

=========================="                      
====== MAIN MENU =======" 
1-Create a new game "
2-Play an existing game"
3-Quit" << endl
Enter the operation : 
 
Ilk menu kullanicinin oyun olusturacagi veya olusturulan oyuna giris yapabilecegi menu.

Ust kisimda olusturulan oyunlarin adlarinin listesini ve mevcut oyunlardaki dolu olan
cell sayisini gorebilirsiniz.

Oyun icerisnde girebileceginiz komutlar oyunu calistirirken soyleniyor

"\n================Welcome The Hex Game Menu===================" 
  Game name  = name 	size : size 	type : type
SAVE file.txt      // This command game saving file.txt" 
LOAD file.txt      // This command Load game named by file.txt" 
CMPR               // To compare with another game " << endl
SIZE               // To make game resize" << endl        
MENU               // If you want to change game or quit " 
====================Have a nice game :)====================" 
-------------------------------------------------------------"	

Burada sizden oyunu ilk aktif ettiginizde ilk olarak size sonra tip isteniyor.
enter size  Ex: 6x6: 
tip 1 = play with friend
tip 2 = paly with computer

Komutlari girerseniz komutun ihtiyacina gore oyun icerisinde yonlendiriliyorsunuz.

SAVE oyunu file.txt icerisine kaydediyor

LOAD file.txt icersindeki verilere gore board yeniden ayarliyor ve static cellCount degiskenini ayarliyor

CMPR Size mevcut oyunlari listeleyip karsilastirmak istediginiz oyunun adini istiyor 
ve sonra 2 boardi bastirip sonucu yazdiriyor

SIZE Mevcut boardi resize ediyor

MENU Ana menuye geri donduruyor Burada yeni oyun olusturup oyunlar arasi gecis yapabilirsiniz







	
   
