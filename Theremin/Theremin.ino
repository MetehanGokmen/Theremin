//Öncelikle Pinleri tanımlıyoruz
//We define the necessary pins 
#define Buzz 10         
#define pingPin 9
#define echoPin 8

//Notaların sayısal değerlerini bir listeye kaydediyoruz.
//İsterseniz tek tek değişken de atayabilirsiniz: const int do= 131; gibi
//Assing a list for notes
//If you want you can do it seperately so you can see the note names. For example const int C3= 131;

int notes[]={131,147,165,175,196,220,247,262,294};



void setup(){
  //Buzzere elektrik vermesi için pinMode komutunu kullanıyoruz
  //i am using pinMode function to power the buzzer
  pinMode(Buzz, OUTPUT); 

  //Seri portu başlatmak için bu kodu yazıyoruz
  //Seri portu kullanmak kişinin kendi tercihidir 
  //ben mesafe sensörünün değerlerini optimize etmek için kullandım
  //Start the serial port btw it is a choice. I used this for the optimization
  Serial.begin(9600);
}

void loop(){
  //Burada duration ve distance diye iki değişken belirliyoruz.
  //Bu değişkenler sayesinde mesafe ölçümünü yapıp o ölçümü bir değişkene atayacağız.
  //We define two variables here to record our measurments.
  long duration, distance;

   //pingPin aslında bizim Trig pinimiz. Ondan bir ses dalgası yollayacağız o yüzden OUTPUT yazıyoruz
   //pingPin is our Trig pin. We'll send a soundwave so we write OUTPUT
   pinMode(pingPin, OUTPUT);

   //loopta sürekli okuyacağımız için aralıklı olarak sesleri yollamamız lazım.
   //o yüzden ilk başta elektrik vermiyoruz
   //We use a loop and We will read the sounds intermittently.
   //So we don't power the pin firstly 
   digitalWrite(pingPin, LOW);
   
   //2 mikro saniyelik bir ara veriyoruz
   //give a 2 microseconds delay
   delayMicroseconds(2);

   //ve elektriği veriyoruz
   //and power up
   digitalWrite(pingPin, HIGH);
   
   //Verdikten sonra 10 mikro saniyelik bir ara veriyoruz
   //after the power up, give a 10 microseconds delay
   delayMicroseconds(10);
   
   //ve Trig pininin elektriğini kesiyoruz
   // and power down the Trig pin
   digitalWrite(pingPin, LOW);
   
   //echo pinimiz bizim sesleri yakaladığımız yer değer okuma işlemi yapacağımız için INPUT yazıyoruz.
   // we'll catch the sounds on th echo Pin. so we write INPUT here
   pinMode(echoPin, INPUT);
   //duration değişkenine değer okunana kadar geçen süreyi kaydediyoruz
   //use the duration to record the time
   duration = pulseIn(echoPin, HIGH);
   
   //distance değişkeni ile de mesafeyi alıyoruz buradaki matematik işlemi santimetre içinidir.  
   //use distance to record the distance of the object from our sensor. calculation is for cm 
   distance = duration / 29 / 2;

  //Mesafe ölçümlerini kontrol etmek için Seri portu kullandığımı söylemiştim.
  //seri porta mesafeyi yazdırıyoruz. Eğer böyle bir isteğiniz yoksa kullanmayabilrsiniz.
  //I said before, I used the serial port for the optimization.
  //we print the serial port the distance.
  Serial.println(distance);

  //Bu blokta 5 santimlik mesafelere göre hangi sesleri çıkracağı yazıyor.
  //Notaları liste şeklinde yazmak, buraya yazarken işlerimizi kolaylaştırdı.
  //this block contains if confdtions to sound which note in which distances. I cut 5 cm pieces. 
  if (distance >= 5 && distance <10){tone(Buzz,notes[0]);} //tone fonksiyonu 3 parametre alır (pin numarası, frekans değeri, çalma süresi)
  if (distance >= 10 && distance <15){tone(Buzz,notes[1]);}// eğer çalma süresi koymazsanız hiç durmadan çalar
  if (distance >= 15 && distance <20){tone(Buzz,notes[2]);}
  if (distance >= 20&& distance <25){tone(Buzz,notes[3]);}
  if (distance >= 25 && distance <30){tone(Buzz,notes[4]);}
  if (distance >= 30 && distance <35){tone(Buzz,notes[5]);}
  if (distance >= 35 && distance <40){tone(Buzz,notes[6]);}
  if (distance >= 40 && distance <45){tone(Buzz,notes[7]);}
  //Delay fonksiyonu ölçümlerin arasını açmamızı ve daha net sesler ve notalar almamızı sağlıyor. 
  //İsterseniz delay fonksiyonunun değeri ile oynayarak kendiniz de sonuçları görebilirsiniz
  //Delay funtion is here to make more clear sounds. If you want you ccan play with it and you can he results.
  delay(500);
  //noTone fonksiyonu eğer üstteki olaylar gerçekleşmezse buzzerin susmasını söylüyor.
  //noTone is here to close the buzzer if there is no object.
  noTone(Buzz);
}
