var textArr = new Array();
var itType = new Array();
var choices = new Array();
var answers = new Array();
var response = new Array();
var hint = new Array();
var modeShowAnsIm = true;
var strTitle = "ĐỀ THI ĐHKA 2011 MÔN HÓA HỌC";
var strSubject = "Hóa học";
var nTime = "90";
var otherInfo = "";

itType[0]=1;
textArr[0]="<b><Ten_De_Thi></b><br>MÔN <Mon_Thi><br>Thời gian : <Thoi_Gian> phút, không kể thời gian phát đề<br>Mã đề : 758";
itType[1]=1;
textArr[1]="Cho biết nguyên tử khối của các nguyên tố:<br>H = 1; C = 12; N = 14; O = 16; Na = 23; Mg = 24; Al = 27; S = 32; Cl = 35,5; K = 39; Ca = 40; Cr = 52; Mn = 55; Fe = 56; Cu = 64; Zn = 65; Br = 80; Ag = 108.<br>";
itType[3]=2;
textArr[3]="Đun nóng m gam hỗn hợp Cu và Fe có tỉ lệ khối lượng tương ứng 7 : 3 với một lượng dung dịch <img src=\"image/1.png\" style=\"vertical-align: -8px\" />. Khi các phản ứng kết thúc, thu dược 0,75 m gam chất rắn, dung dịch X và 5,6 lít hỗn hợp khí (đktc) gồm NO và <img src=\"image/2.png\" style=\"vertical-align: -8px\" /> (không có sản phẩm khử khác của <img src=\"image/3.png\" style=\"vertical-align: -5px\" />). Biết lượng <img src=\"image/4.png\" style=\"vertical-align: -8px\" /> đã phản ứng là 44,1 gam. Giá trị của m là";
choices[3]=new Array();
choices[3][0]="44,8.";
choices[3][1]="33,6.";
choices[3][2]="40,5.";
choices[3][3]="50,4.";
answers[3]=3;
itType[4]=2;
textArr[4]="Đốt cháy hoàn toàn 3,42 gam hỗn hợp gồm axit acrylic, vinyl axetat, metyl acrylat và axit oleic, rồi hấp thụ toàn bộ sản phẩm cháy vào dung dịch <img src=\"image/5.png\" style=\"vertical-align: -8px\" /> (dư). Sau phản ứng thu được 18 gam kết tủa và dung dịch X. Khối lượng X so với khối lượng dung dịch <img src=\"image/6.png\" style=\"vertical-align: -8px\" /> ban đầu đã thay đổi như thế nào?";
choices[4]=new Array();
choices[4][0]="Tăng 2,70 gam.";
choices[4][1]="Giảm 7,74 gam.";
choices[4][2]="Tăng 7,92 gam.";
choices[4][3]="Giảm 7,38 gam.";
answers[4]=3;
itType[5]=2;
textArr[5]="Cho axit salixylic (axit 0-hidroxibenzoic) phản ứng với anhidrit axetic, thu được axit axetylsalixylic (<img src=\"image/7.png\" style=\"vertical-align: -8px\" />) dùng làm thuốc cảm (aspirin). Để phản ứng hoàn toàn với 43,2 gam axit axetylsalixylic cần vừa đủ V lít dung dịch KOH 1M. Giá trị của V là";
choices[5]=new Array();
choices[5][0]="0.48.";
choices[5][1]="0,72.";
choices[5][2]="0,24.";
choices[5][3]="0,96.";
answers[5]=1;
itType[6]=2;
textArr[6]="Hòa tan 13,68 gam muối <img src=\"image/8.png\" style=\"vertical-align: -8px\" /> vào nước được dung dịch X. Điện phân X (với điện cực trơ, cường độ dòng điện không đổi) trong thời gian t giây, được y gam kim loại M duy nhất ở catot và 0,035 mol khí ở anot. Còn nếu thời gian điện phân là 2t giây thì tổng số mol khí thu được ở cả hai điện cực là 0,1245 mol. Giá trị của y là";
choices[6]=new Array();
choices[6][0]="4,788.";
choices[6][1]="1,680.";
choices[6][2]="4,480.";
choices[6][3]="3,920.";
answers[6]=2;
itType[7]=2;
textArr[7]="Cho dãy các chất: NaOH, <img src=\"image/9.png\" style=\"vertical-align: -8px\" />, <img src=\"image/10.png\" style=\"vertical-align: -8px\" />, <img src=\"image/11.png\" style=\"vertical-align: -8px\" />, <img src=\"image/12.png\" style=\"vertical-align: -8px\" />. Số chất trong dãy có tính chất lưỡng tính là";
choices[7]=new Array();
choices[7][0]="3.";
choices[7][1]="1.";
choices[7][2]="2.";
choices[7][3]="4.";
answers[7]=3;
itType[8]=2;
textArr[8]="Khi nói về peptit và protein, phát biểu nào sau đây là sai?";
choices[8]=new Array();
choices[8][0]="Liên kết của nhóm CO với nhóm NH giữa hai đơn vị  α-amino axit được gọi là liên kết peptit.";
choices[8][1]="Thủy phân hoàn toàn protein đơn giản thu được các  α-amino axit.";
choices[8][2]="Protein có phản ứng màu biure với <img src=\"image/13.png\" style=\"vertical-align: -8px\" />.";
choices[8][3]="Tất cả các protein đều tan trong nước tạo thành dung dịch keo.";
answers[8]=3;
itType[9]=2;
textArr[9]="Tiến hành các thí nghiệm sau:<br>	(1) Cho dung dịch NaOH vào dung dịch <img src=\"image/14.png\" style=\"vertical-align: -8px\" />.<br>	(2) Cho dung dịch HCl tới dư vào dung dịch <img src=\"image/15.png\" style=\"vertical-align: -8px\" /> (hoặc <img src=\"image/16.png\" style=\"vertical-align: -8px\" />).<br>	(3) Sục khí <img src=\"image/17.png\" style=\"vertical-align: -8px\" /> vào dung dịch <img src=\"image/18.png\" style=\"vertical-align: -8px\" />.<br>	(4) Sục khí <img src=\"image/19.png\" style=\"vertical-align: -8px\" /> tới dư vào dung dịch <img src=\"image/20.png\" style=\"vertical-align: -8px\" />.<br>	(5) Sục khí <img src=\"image/21.png\" style=\"vertical-align: -8px\" /> tới dư vào dung dịch <img src=\"image/22.png\" style=\"vertical-align: -8px\" /> (hoặc <img src=\"image/23.png\" style=\"vertical-align: -8px\" />).<br>	(6) Sục khí etilen vào dung dịch <img src=\"image/24.png\" style=\"vertical-align: -8px\" />.<br>Sau khi các phản ứng kết thúc, có bao nhiêu thí nghiệm thu được kết tủa?";
choices[9]=new Array();
choices[9][0]="3.";
choices[9][1]="5.";
choices[9][2]="6.";
choices[9][3]="4.";
answers[9]=3;
itType[10]=2;
textArr[10]="Dãy gồm các chất đều có thể làm mất tính cứng tạm thời của nước là:";
choices[10]=new Array();
choices[10][0]="<img src=\"image/25.png\" style=\"vertical-align: -8px\" />";
choices[10][1]="<img src=\"image/26.png\" style=\"vertical-align: -8px\" />";
choices[10][2]="<img src=\"image/27.png\" style=\"vertical-align: -8px\" />";
choices[10][3]="<img src=\"image/28.png\" style=\"vertical-align: -8px\" />";
answers[10]=0;
itType[11]=2;
textArr[11]="Phát biểu nào sau đây là sai?";
choices[11]=new Array();
choices[11][0]="Bán kính nguyên tử của clo lớn hơn bán kính nguyên tử của flo.";
choices[11][1]="Tính axit của HF mạnh hơn tính axit của HCl.";
choices[11][2]="Độ âm điện của brom lớn hơn độ âm điện của iot.";
choices[11][3]="Tính khử của ion <img src=\"image/29.png\" style=\"vertical-align: -5px\" /> lớn hơn tính khử của ion <img src=\"image/30.png\" style=\"vertical-align: -5px\" />.";
answers[11]=1;
itType[12]=2;
textArr[12]="Phèn chua được dùng trong ngành công nghiệp thuộc da, công nghiệp giấy, chất cầm màu trong ngành nhuộm vải, chất làm trong nước. Công thức hóa học của phèn chua là:";
choices[12]=new Array();
choices[12][0]="<img src=\"image/31.png\" style=\"vertical-align: -8px\" />";
choices[12][1]="<img src=\"image/32.png\" style=\"vertical-align: -8px\" />";
choices[12][2]="<img src=\"image/33.png\" style=\"vertical-align: -8px\" />";
choices[12][3]="<img src=\"image/34.png\" style=\"vertical-align: -8px\" />";
answers[12]=2;
itType[13]=2;
textArr[13]="Sản phẩm hữu cơ của phản ứng nào sau đây <b>không</b> dùng để chế tạo tơ tổng hợp?";
choices[13]=new Array();
choices[13][0]="Trùng hợp vinyl xianua.";
choices[13][1]="Trùng ngưng axit ε-aminocaproic.";
choices[13][2]="Trùng hợp metyl metacrylat.";
choices[13][3]="Trùng ngưng hexametylenđiamin với axit ađipic.";
answers[13]=2;
itType[14]=2;
textArr[14]="Điện phân dung dịch gồm 7,45 gam KCl và 28,2 gam <img src=\"image/35.png\" style=\"vertical-align: -8px\" />. (điện cực trơ, màng ngăn xốp) đến khi khối lượng dung dịch giảm đi 10,75 gam thì ngừng điện phân (giả thiết lượng nước bay hơi không đáng kể). Tất cả các chất tan trong dung dịch sau điện phân là:";
choices[14]=new Array();
choices[14][0]="<img src=\"image/36.png\" style=\"vertical-align: -8px\" />";
choices[14][1]="<img src=\"image/37.png\" style=\"vertical-align: -8px\" />";
choices[14][2]="<img src=\"image/38.png\" style=\"vertical-align: -8px\" />";
choices[14][3]="<img src=\"image/39.png\" style=\"vertical-align: -8px\" />";
answers[14]=1;
itType[15]=2;
textArr[15]="Chia hỗn hợp X gồm K, Al và Fe thành hai phần bằng nhau.<br>	- Cho phần một vào dung dịch KOH (dư) thu được 0,784 lít khí <img src=\"image/40.png\" style=\"vertical-align: -8px\" /> (đktc).<br>	- Cho phần hai vào một lượng dư <img src=\"image/41.png\" style=\"vertical-align: -8px\" />, thu được 0,448 lít khí <img src=\"image/42.png\" style=\"vertical-align: -8px\" /> (đktc) và m gam hỗn hợp kim loại Y. Hòa tan hoàn toàn Y vào dung dịch HCl  (dư) thu được 0,56 lít khí <img src=\"image/43.png\" style=\"vertical-align: -8px\" /> (đktc).<br>	Khối lượng (tính theo gam) của K, Al, Fe tính trong mỗi phần hỗn hợp X lần lượt là :";
choices[15]=new Array();
choices[15][0]="0,39 ; 0,54 ; 1,40.";
choices[15][1]="0,78; 0,54; 1,12.";
choices[15][2]="0,39; 0,54; 0,56.";
choices[15][3]="0,78; 1,08; 0,56.";
answers[15]=2;
itType[16]=2;
textArr[16]="Cho dãy các chất phenylamoni clorua, benzyl clorua, isopropyl clorua, m – crezol, ancol benzylic, natri phenolat, anlyl clorua. Số chất trong dãy tác dụng được với dung dịch NaOH loãng đun nóng là";
choices[16]=new Array();
choices[16][0]="4.";
choices[16][1]="3.";
choices[16][2]="5.";
choices[16][3]="6";
answers[16]=2;
itType[17]=2;
textArr[17]="Hợp chất hữu cơ X chứa vòng benzen có công thức phân tử trùng với công thức đơn giản nhất. Trong X, tỉ lệ khối lượng các nguyên tố là <img src=\"image/44.png\" style=\"vertical-align: -8px\" /> = 21 : 2 : 8. Biết khi X phản ứng hoàn toàn với Na thì thu được số mol khí hiđro bằng số mol của X đã phản ứng. X có bao nhiêu đồng phân (chứa vòng benzen) thỏa mãn các tính chất trên?";
choices[17]=new Array();
choices[17][0]="10.";
choices[17][1]="9.";
choices[17][2]="7.";
choices[17][3]="3.";
answers[17]=1;
itType[18]=2;
textArr[18]="Khi so sánh <img src=\"image/45.png\" style=\"vertical-align: -8px\" /> với <img src=\"image/46.png\" style=\"vertical-align: -8px\" />, phát biểu không đúng là :";
choices[18]=new Array();
choices[18][0]="Trong <img src=\"image/47.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/48.png\" style=\"vertical-align: -8px\" /> , nitơ đều có số oxi hóa -3.";
choices[18][1]="<img src=\"image/49.png\" style=\"vertical-align: -8px\" /> có tính bazơ, <img src=\"image/50.png\" style=\"vertical-align: -8px\" /> có tính axit.";
choices[18][2]="Phân tử <img src=\"image/51.png\" style=\"vertical-align: -8px\" /> và ion <img src=\"image/52.png\" style=\"vertical-align: -8px\" /> đều chứa liên kết cộng hóa trị.";
choices[18][3]="Trong <img src=\"image/53.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/54.png\" style=\"vertical-align: -8px\" />, nitơ đều có cộng hóa trị 3.";
answers[18]=3;
itType[19]=2;
textArr[19]="Thành phần % khối lượng của nitơ trong hợp chất hữu cơ <img src=\"image/55.png\" style=\"vertical-align: -8px\" /> là 23,73 %. Số đồng phân amin bậc một thỏa mãn các dữ kiện trên là";
choices[19]=new Array();
choices[19][0]="3.";
choices[19][1]="2.";
choices[19][2]="4.";
choices[19][3]="1.";
answers[19]=1;
itType[20]=2;
textArr[20]="Hấp thụ hoàn toàn 0,672 lít khí <img src=\"image/56.png\" style=\"vertical-align: -8px\" /> (đktc) vào một lít dung dịch gồm NaOH 0,025M và <img src=\"image/57.png\" style=\"vertical-align: -8px\" /> 0,0125M, thu được x gam kết tủa. Giá trị của x là";
choices[20]=new Array();
choices[20][0]="2,00.";
choices[20][1]="0,75.";
choices[20][2]="1,25.";
choices[20][3]="1,00.";
answers[20]=2;
itType[21]=2;
textArr[21]="Đốt cháy hoàn toàn x gam hỗn hợp gồm hai axit cacboxylic hai chức, mạch hở và đều có một liên kết đôi C=C trong phân tử, thu được V lít khí <img src=\"image/58.png\" style=\"vertical-align: -8px\" /> (đktc) và y mol <img src=\"image/59.png\" style=\"vertical-align: -8px\" />. Biểu thức liên hệ giữa các giá trị x, y và V là";
choices[21]=new Array();
choices[21][0]="<img src=\"image/60.png\" style=\"vertical-align: -17px\" />";
choices[21][1]="<img src=\"image/61.png\" style=\"vertical-align: -17px\" />";
choices[21][2]="<img src=\"image/62.png\" style=\"vertical-align: -17px\" />";
choices[21][3]="<img src=\"image/63.png\" style=\"vertical-align: -17px\" />";
answers[21]=1;
itType[22]=2;
textArr[22]="Este X được tạo thành từ etylen glicol và hai axit cacboxylic đơn chức. Trong phân tử este, số nguyên tử cacbon nhiều hơn số nguyên tử oxi là 1. Khi cho m gam X tác dụng với dung dịch NaOH (dư) thì lượng NaOH đã phản ứng là 10 gam. Giá trị của m là";
choices[22]=new Array();
choices[22][0]="14,5.";
choices[22][1]="17,5.";
choices[22][2]="15,5.";
choices[22][3]="16,5.";
answers[22]=3;
itType[23]=2;
textArr[23]="Hợp chất nào của canxi được dùng để đúc tượng, bó bột khi gãy xương?";
choices[23]=new Array();
choices[23][0]="Thạch cao nung (<img src=\"image/64.png\" style=\"vertical-align: -8px\" />).";
choices[23][1]="Thạch cao sống (<img src=\"image/65.png\" style=\"vertical-align: -8px\" />).";
choices[23][2]="Đá vôi (<img src=\"image/66.png\" style=\"vertical-align: -8px\" />).";
choices[23][3]="Vôi sống (CaO).";
answers[23]=0;
itType[24]=2;
textArr[24]="Cho 13,8 gam chất hữu cơ X có công thức phân tử <img src=\"image/67.png\" style=\"vertical-align: -8px\" /> tác dụng với một lượng dư dung dịch <img src=\"image/68.png\" style=\"vertical-align: -8px\" /> trong <img src=\"image/69.png\" style=\"vertical-align: -8px\" />, thu được 45,9 gam kết tủa. X có bao nhiêu đồng phân cấu tạo thỏa mãn tính chất trên?";
choices[24]=new Array();
choices[24][0]="4.";
choices[24][1]="6.";
choices[24][2]="2.";
choices[24][3]="5.";
answers[24]=0;
itType[25]=2;
textArr[25]="Đốt cháy hoàn toàn x mol axit cacboxylic E, thu được y mol <img src=\"image/70.png\" style=\"vertical-align: -8px\" /> và z mol <img src=\"image/71.png\" style=\"vertical-align: -8px\" /> (với z = y - x). Cho x mol E tác dụng với <img src=\"image/72.png\" style=\"vertical-align: -8px\" /> (dư) thu được y mol <img src=\"image/73.png\" style=\"vertical-align: -8px\" />. Tên của E là";
choices[25]=new Array();
choices[25][0]="axit acrylic.";
choices[25][1]="axit ađipic.";
choices[25][2]="axit oxalic.";
choices[25][3]="axit fomic.";
answers[25]=2;
itType[26]=2;
textArr[26]="Cho 0,87 gam hỗn hợp gồm Fe, Cu và Al vào bình đựng 300 ml dung dịch <img src=\"image/74.png\" style=\"vertical-align: -8px\" /> 0,1M. Sau khi các phản ứng xảy ra hoàn toàn, thu được 0,32 gam chất rắn và 448 ml khí (đktc) thoát ra. Thêm tiếp vào bình 0,425 gam <img src=\"image/75.png\" style=\"vertical-align: -8px\" />, khi các phản ứng kết thúc thì thể tích khí NO (đktc, sản phẩm khử duy nhất) tạo thành và khối lượng muối trong dung dịch là";
choices[26]=new Array();
choices[26][0]="0,224 lít và 3,750 gam";
choices[26][1]="0,112 lít và 3,750 gam";
choices[26][2]="0,112 lít và 3,865 gam";
choices[26][3]="0,224 lít và 3,865 gam";
answers[26]=2;
itType[27]=2;
textArr[27]="Quặng sắt manhetit có thành phần là";
choices[27]=new Array();
choices[27][0]="<img src=\"image/76.png\" style=\"vertical-align: -8px\" />.";
choices[27][1]="<img src=\"image/77.png\" style=\"vertical-align: -8px\" />.";
choices[27][2]="<img src=\"image/78.png\" style=\"vertical-align: -8px\" />.";
choices[27][3]="<img src=\"image/79.png\" style=\"vertical-align: -8px\" />.";
answers[27]=2;
itType[28]=2;
textArr[28]="Hỗn hợp X gồm axit axetic, axit fomic và axit oxalic. Khi cho m gam X tác dụng với <img src=\"image/80.png\" style=\"vertical-align: -8px\" /> (dư) thì thu được 15,68 lít khí <img src=\"image/81.png\" style=\"vertical-align: -8px\" /> (đktc). Mặt khác, đốt cháy hoàn toàn m gam X cần 8,96 lít khí <img src=\"image/82.png\" style=\"vertical-align: -8px\" /> (đktc), thu được 35,2 gam <img src=\"image/83.png\" style=\"vertical-align: -8px\" /> và y mol <img src=\"image/84.png\" style=\"vertical-align: -8px\" />. Giá trị của y là";
choices[28]=new Array();
choices[28][0]="0,3.";
choices[28][1]="0,6.";
choices[28][2]="0,8.";
choices[28][3]="0,2.";
answers[28]=1;
itType[29]=2;
textArr[29]="Hỗn hợp X gồm <img src=\"image/85.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/86.png\" style=\"vertical-align: -8px\" /> có cùng số mol. Lấy một lượng  hỗn hợp X cho qua chất xúc tác nung nóng, thu được hỗn hợp Y gồm <img src=\"image/87.png\" style=\"vertical-align: -8px\" />, <img src=\"image/88.png\" style=\"vertical-align: -8px\" />, <img src=\"image/89.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/90.png\" style=\"vertical-align: -8px\" />. Sục Y vào dung dịch brom (dư) thì khối lượng bình brom tăng 10,8 gam và thoát ra 4,48 lít hỗn hợp khí (đktc) có tỉ khối so với <img src=\"image/91.png\" style=\"vertical-align: -8px\" /> là 8. Thể tích <img src=\"image/92.png\" style=\"vertical-align: -8px\" /> (đktc) cần để đốt cháy hoàn toàn hỗn hợp Y là";
choices[29]=new Array();
choices[29][0]="33,6 lít.";
choices[29][1]="44,8 lít.";
choices[29][2]="22,4 lít.";
choices[29][3]="26,88 lít.";
answers[29]=0;
itType[30]=2;
textArr[30]="Trung hòa 3,88 gam hỗn hợp X gồm hai axit cacboxylic no, đơn chức, mạch hở bằng dung dịch NaOH, cô cạn toàn bộ dung dịch sau phản ứng thu được 5,2 gam muối khan. Nếu đốt cháy hoàn toàn 3,88 gam X thì thể tích oxi (đktc) cần dùng là";
choices[30]=new Array();
choices[30][0]="3,36 lít";
choices[30][1]="4,48 lít.";
choices[30][2]="2,24 lít";
choices[30][3]="1,12 lít.";
answers[30]=0;
itType[31]=2;
textArr[31]="Xenlulozơ trinitrat được điều chế từ phản ứng giữa axit nitric với xenlulozơ (hiệu suất phản ứng 60% tính theo xenlulozơ). Nếu dùng 2 tấn xenlulozơ thì khối lượng xenlulozơ trinitrat điều chế được là";
choices[31]=new Array();
choices[31][0]="2,97 tấn.";
choices[31][1]="3,67 tấn.";
choices[31][2]="1,10 tấn.";
choices[31][3]="2,20 tấn.";
answers[31]=3;
itType[32]=2;
textArr[32]="Đốt cháy hoàn toàn andehit X, thu được thể tích khí <img src=\"image/93.png\" style=\"vertical-align: -8px\" /> bằng thể tích hơi nước (trong cùng điều kiện nhiệt độ, áp suất). Khi cho 0,01 mol X tác dụng với một lượng dư dung dịch <img src=\"image/94.png\" style=\"vertical-align: -8px\" /> trong <img src=\"image/95.png\" style=\"vertical-align: -8px\" /> thì thu được 0,04 mol Ag. X là";
choices[32]=new Array();
choices[32][0]="anđehit no, mạch hở, hai chức.";
choices[32][1]="anđehit fomic.";
choices[32][2]="anđehit axetic.";
choices[32][3]="anđehit không no, mạch hở, hai chức.";
answers[32]=1;
itType[33]=2;
textArr[33]="Thủy phân hết m gam tetrapeptit Ala–Ala–Ala–Ala (mạch hở) thu được hỗn hợp gồm 28,48 gam Ala, 32 gam Ala–Ala và 27,72 gam Ala–Ala–Ala. Giá trị của m là:";
choices[33]=new Array();
choices[33][0]="111,74";
choices[33][1]="81,54";
choices[33][2]="90,6";
choices[33][3]="66,44";
answers[33]=1;
itType[34]=2;
textArr[34]="Đốt cháy hoàn toàn hỗn hợp X gồm <img src=\"image/96.png\" style=\"vertical-align: -8px\" />, <img src=\"image/97.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/98.png\" style=\"vertical-align: -8px\" /> (số mol mỗi chất bằng nhau) thu được 0,09 mol <img src=\"image/99.png\" style=\"vertical-align: -8px\" />. Nếu lấy cùng một lượng hỗn hợp X như trên tác dụng với một lượng dư dung dịch <img src=\"image/100.png\" style=\"vertical-align: -8px\" /> trong <img src=\"image/101.png\" style=\"vertical-align: -8px\" />, thì khối lượng kết tủa thu được lớn hơn 4gam. Công thức cấu tạo của <img src=\"image/102.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/103.png\" style=\"vertical-align: -8px\" /> trong X lần lượt là:";
choices[34]=new Array();
choices[34][0]="<img src=\"image/104.png\" style=\"vertical-align: -8px\" />";
choices[34][1]="<img src=\"image/105.png\" style=\"vertical-align: -8px\" />";
choices[34][2]="<img src=\"image/106.png\" style=\"vertical-align: -8px\" />";
choices[34][3]="<img src=\"image/107.png\" style=\"vertical-align: -8px\" />";
answers[34]=2;
itType[35]=2;
textArr[35]="Số đồng phân của amino axit có công thức phân tử <img src=\"image/108.png\" style=\"vertical-align: -8px\" /> là:";
choices[35]=new Array();
choices[35][0]="4.";
choices[35][1]="1.";
choices[35][2]="3.";
choices[35][3]="2.";
answers[35]=3;
itType[36]=2;
textArr[36]="Khối lượng riêng của canxi kim loại là 1,55 g/<img src=\"image/109.png\" style=\"vertical-align: -5px\" />. Giả thiết rằng trong tinh thể canxi các nguyên tử là những hình cầu chiếm 74% thể tích tinh thể, phần còn lại là khe rỗng. Bán kính nguyên tử canxi tính theo lý thuyết là:";
choices[36]=new Array();
choices[36][0]="0,185 nm.";
choices[36][1]="0,196 nm.";
choices[36][2]="0,155 nm.";
choices[36][3]="0,168 nm.";
answers[36]=1;
itType[37]=2;
textArr[37]="Cho 7,68 gam Cu vào 200ml dung dịch gồm <img src=\"image/110.png\" style=\"vertical-align: -8px\" /> 0,6M và <img src=\"image/111.png\" style=\"vertical-align: -8px\" /> 0,5M. Sau khi các phản ứng xảy ra hoàn toàn (sản phẩm khử duy nhất là NO), cô cạn cẩn thận toàn bộ dung dịch sau phản ứng thì khối lượng muối khan thu được là:";
choices[37]=new Array();
choices[37][0]="19,76 gam.";
choices[37][1]="20,16 gam.";
choices[37][2]="19,20 gam.";
choices[37][3]="22,56 gam.";
answers[37]=0;
itType[38]=2;
textArr[38]="Nung m gam hỗn hợp X gồm FeS và <img src=\"image/112.png\" style=\"vertical-align: -8px\" />, trong một bình kín chứa không khí (gồm 20 % thể tích <img src=\"image/113.png\" style=\"vertical-align: -8px\" /> và 80% thể tích <img src=\"image/114.png\" style=\"vertical-align: -8px\" />) đến khi các phản ứng này xảy ra hoàn toàn, thu được một chất rắn duy nhất và hỗn hợp khí Y có thành phần thể tích: 84,8% <img src=\"image/115.png\" style=\"vertical-align: -8px\" />, 14% <img src=\"image/116.png\" style=\"vertical-align: -8px\" />, còn lại là <img src=\"image/117.png\" style=\"vertical-align: -8px\" />. Phần trăm khối lượng của FeS trong hỗn hợp X là:";
choices[38]=new Array();
choices[38][0]="59,46%";
choices[38][1]="19,64%";
choices[38][2]="42,31%";
choices[38][3]="26,83%";
answers[38]=1;
itType[39]=2;
textArr[39]="Cho cân bằng hóa học: <img src=\"image/118.png\" style=\"vertical-align: -8px\" />; <img src=\"image/119.png\" style=\"vertical-align: -5px\" /><br>	Cân bằng không bị chuyển dịch khi:";
choices[39]=new Array();
choices[39][0]="giảm nồng độ HI.";
choices[39][1]="tăng nồng độ <img src=\"image/120.png\" style=\"vertical-align: -8px\" />.";
choices[39][2]="tăng nhiệt độ của hệ.";
choices[39][3]="giảm áp suất chung của hệ.";
answers[39]=3;
itType[40]=2;
textArr[40]="Cho dãy các chất và ion: <img src=\"image/121.png\" style=\"vertical-align: -8px\" />. Số chất và ion vừa có tính oxi hóa vừa có tính khử là:";
choices[40]=new Array();
choices[40][0]="4.";
choices[40][1]="5.";
choices[40][2]="6.";
choices[40][3]="8.";
answers[40]=1;
itType[41]=2;
textArr[41]="Thực hiện các thí nghiệm sau:<br>(1) Đốt dây sắt trong khí clo.<br>(2) Đốt nóng hỗn hợp bột Fe và S (trong điều kiện không có oxi)<br>(3) Cho FeO vào dung dịch <img src=\"image/122.png\" style=\"vertical-align: -8px\" /> (loãng, dư)<br>(4) Cho Fe vào dung dịch <img src=\"image/123.png\" style=\"vertical-align: -8px\" /><br>(5) Cho Fe vào dung dịch <img src=\"image/124.png\" style=\"vertical-align: -8px\" /> (loãng, dư)<br>Có bao nhiêu thí nghiệm tạo ra muối sắt (II)?";
choices[41]=new Array();
choices[41][0]="3.";
choices[41][1]="2.";
choices[41][2]="1.";
choices[41][3]="4.";
answers[41]=0;
itType[42]=2;
textArr[42]="Trong các thí nghiệm sau:<br>(1) Cho <img src=\"image/125.png\" style=\"vertical-align: -8px\" /> tác dụng với axit HF.<br>(2) Cho khí <img src=\"image/126.png\" style=\"vertical-align: -8px\" /> tác dụng với khí <img src=\"image/127.png\" style=\"vertical-align: -8px\" />.<br>(3) Cho khí <img src=\"image/128.png\" style=\"vertical-align: -8px\" /> tác dụng với CuO đun nóng.<br>(4) Cho <img src=\"image/129.png\" style=\"vertical-align: -8px\" /> tác dụng với HCl đặc.<br>(5) Cho Si đơn chất tác dụng với dung dịch NaOH.<br>(6) Cho khí <img src=\"image/130.png\" style=\"vertical-align: -8px\" /> tác dụng với Ag.<br>(7) Cho dung dịch <img src=\"image/131.png\" style=\"vertical-align: -8px\" /> tác dụng với dung dịch <img src=\"image/132.png\" style=\"vertical-align: -8px\" /> đung nóng.<br>Số thí nghiệm tạo ra đơn chất là:";
choices[42]=new Array();
choices[42][0]="4.";
choices[42][1]="7.";
choices[42][2]="5.";
choices[42][3]="6.";
answers[42]=3;
itType[46]=2;
textArr[46]="Cho buta-1,3-đien phản ứng cộng với <img src=\"image/133.png\" style=\"vertical-align: -8px\" /> theo tỉ lệ mol 1: 1. Số dẫn xuất đibrom (đồng phân cấu tạo và đồng phân hình học) thu được là:";
choices[46]=new Array();
choices[46][0]="1.";
choices[46][1]="3.";
choices[46][2]="2.";
choices[46][3]="4.";
answers[46]=1;
itType[47]=2;
textArr[47]="Dung dịch nào sau đây làm quỳ tím đổi thành màu xanh";
choices[47]=new Array();
choices[47][0]="Dung dịch lysin";
choices[47][1]="Dung dịch alanin";
choices[47][2]="Dung dịch glyxin";
choices[47][3]="Dung dịch valin";
answers[47]=0;
itType[48]=2;
textArr[48]="Khi điện phân dung dịch NaCl (cực âm bằng sắt, cực dương bằng than chì, có màng ngăn xốp) thì";
choices[48]=new Array();
choices[48][0]="ở cực âm xảy ra quá trình khử <img src=\"image/134.png\" style=\"vertical-align: -8px\" /> và ở cực dương xảy ra quá trình oxi hóa ion <img src=\"image/135.png\" style=\"vertical-align: -5px\" />.";
choices[48][1]="ở cực âm xảy ra quá trình oxi hóa <img src=\"image/136.png\" style=\"vertical-align: -8px\" /> và ở cực dương xảy ra quá trình khử ion <img src=\"image/137.png\" style=\"vertical-align: -5px\" />.";
choices[48][2]="ở cực âm xẩy ra quá trình khử ion <img src=\"image/138.png\" style=\"vertical-align: -5px\" /> và ở cực dương xảy ra quá trình oxi hóa ion <img src=\"image/139.png\" style=\"vertical-align: -5px\" />.";
choices[48][3]="ở cực dương xảy ra quá trình oxi hóa ion <img src=\"image/140.png\" style=\"vertical-align: -5px\" /> và ở cực âm xảy ra quá trình khử ion <img src=\"image/141.png\" style=\"vertical-align: -5px\" />";
answers[48]=0;
itType[49]=2;
textArr[49]="Cấu hình electron của ion <img src=\"image/142.png\" style=\"vertical-align: -5px\" /> và <img src=\"image/143.png\" style=\"vertical-align: -5px\" /> lần lượt là";
choices[49]=new Array();
choices[49][0]="<img src=\"image/144.png\" style=\"vertical-align: -8px\" />";
choices[49][1]="<img src=\"image/145.png\" style=\"vertical-align: -8px\" />";
choices[49][2]="<img src=\"image/146.png\" style=\"vertical-align: -5px\" />";
choices[49][3]="<img src=\"image/147.png\" style=\"vertical-align: -8px\" />";
answers[49]=2;
itType[50]=2;
textArr[50]="Ancol etylic được điều chế từ tinh bột bằng phương pháp lên men với hiệu suất toàn bộ quá trình là 90%. Hấp thụ toàn bộ lượng  <img src=\"image/148.png\" style=\"vertical-align: -8px\" /> sinh ra khi lên men m gam tinh bột vào nước vôi trong, thu được 330 gam kết tủa và dung dịch X. Biết khối lượng X giảm đi so với khối lượng nước vôi trong ban đầu là 132 gam. Giá trị của m là";
choices[50]=new Array();
choices[50][0]="297.";
choices[50][1]="405.";
choices[50][2]="486.";
choices[50][3]="324.";
answers[50]=1;
itType[51]=2;
textArr[51]="Hóa hơi 15,52 gam hỗn hợp gồm một axit no đơn chức X và một axit no đa chức Y (số mol X lớn hơn số mol Y), thu được một thể tích hơi bằng thể tích của 5,6 gam <img src=\"image/149.png\" style=\"vertical-align: -8px\" /> (đo trong cùng điều kiện nhiệt độ, áp suất). Nếu đốt cháy toàn bộ hỗn hợp hai axit trên thì thu được 10,752 lít <img src=\"image/150.png\" style=\"vertical-align: -8px\" /> (đktc). Công  thức cấu tạo của X, Y lần lượt là";
choices[51]=new Array();
choices[51][0]="<img src=\"image/151.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/152.png\" style=\"vertical-align: -5px\" />";
choices[51][1]="<img src=\"image/153.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/154.png\" style=\"vertical-align: -8px\" />";
choices[51][2]="<img src=\"image/155.png\" style=\"vertical-align: -5px\" /> và <img src=\"image/156.png\" style=\"vertical-align: -5px\" />";
choices[51][3]="<img src=\"image/157.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/158.png\" style=\"vertical-align: -8px\" />";
answers[51]=3;
itType[52]=2;
textArr[52]="Nhóm những chất khí (hoặc hơi) nào dưới đây đều gây hiệu ứng nhà kính khi nồng độ của chúng trong khí quyển vượt quá tiêu chuẩn cho phép?";
choices[52]=new Array();
choices[52][0]="<img src=\"image/159.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/160.png\" style=\"vertical-align: -8px\" />";
choices[52][1]="<img src=\"image/161.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/162.png\" style=\"vertical-align: -8px\" />";
choices[52][2]="<img src=\"image/163.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/164.png\" style=\"vertical-align: -8px\" />";
choices[52][3]="<img src=\"image/165.png\" style=\"vertical-align: -8px\" /> và <img src=\"image/166.png\" style=\"vertical-align: -5px\" />";
answers[52]=2;
itType[53]=2;
textArr[53]="Cho 2,7 gam hỗn hợp bột X gồm Fe và Zn tác dụng với dung dịch <img src=\"image/167.png\" style=\"vertical-align: -8px\" /> .Sau một thời gian, thu được dung dịch Y và 2,84 gam chất rắn Z. Cho toàn bộ Z vào dung dịch <img src=\"image/168.png\" style=\"vertical-align: -8px\" /> (loãng, dư), sau khi các phản ứng kết thúc thì khối lượng chất rắn giảm 0,28 gam và dung dịch thu được chỉ chứa một muối duy nhất. Phần trăm khối lượng của Fe trong X là";
choices[53]=new Array();
choices[53][0]="58,52%.";
choices[53][1]="41,48%.";
choices[53][2]="48,15%.";
choices[53][3]="51,85%.";
answers[53]=3;
itType[54]=2;
textArr[54]="Cho hỗn hợp X gồm <img src=\"image/169.png\" style=\"vertical-align: -8px\" /> và Cu tác dụng với dung dịch HCl (dư) thu được dung dịch Y và phần không tan Z. Cho Y tác dụng với dung dịch NaOH (loãng, dư) thu được kết tủa";
choices[54]=new Array();
choices[54][0]="<img src=\"image/170.png\" style=\"vertical-align: -8px\" />";
choices[54][1]="<img src=\"image/171.png\" style=\"vertical-align: -8px\" />";
choices[54][2]="<img src=\"image/172.png\" style=\"vertical-align: -8px\" />";
choices[54][3]="<img src=\"image/173.png\" style=\"vertical-align: -8px\" />";
answers[54]=0;
itType[55]=2;
textArr[55]="X, Y, Z là các hợp chất mạch hở, bền có cùng công thức phân tử <img src=\"image/174.png\" style=\"vertical-align: -8px\" />. X tác dụng được với Na và không có phản ứng tráng bạc. Y không tác dụng được với Na nhưng có phản ứng tráng bạc. Z không tác dụng được với Na và không có phản ứng tráng bạc. Cac chất X, Y, Z lần lượt là:";
choices[55]=new Array();
choices[55][0]="<img src=\"image/175.png\" style=\"vertical-align: -8px\" />";
choices[55][1]="<img src=\"image/176.png\" style=\"vertical-align: -8px\" />";
choices[55][2]="<img src=\"image/177.png\" style=\"vertical-align: -8px\" />";
choices[55][3]="<img src=\"image/178.png\" style=\"vertical-align: -8px\" />";
answers[55]=1;
itType[58]=2;
textArr[58]="Phát biểu nào sau đây về anđêhit và xeton là sai?";
choices[58]=new Array();
choices[58][0]="Hiđro xianua cộng vào nhóm cacbonyl tạo thành sản phẩm không bền.";
choices[58][1]="Anđêhit fomic tác dụng với <img src=\"image/179.png\" style=\"vertical-align: -8px\" /> tạo thành sản phẩm không bền.";
choices[58][2]="Axetanđehit phản ứng được với nước brom.";
choices[58][3]="Axeton không phản ứng được với nước brom.";
answers[58]=0;
itType[59]=2;
textArr[59]="Không khí trong phòng thí nghiệm bị ô nhiễm bởi khí clo. Để khử độc, có thể xịt vào không khí dung dịch nào sau đây?";
choices[59]=new Array();
choices[59][0]="Dung dịch <img src=\"image/180.png\" style=\"vertical-align: -8px\" /> loãng.";
choices[59][1]="Dung dịch NaCl.";
choices[59][2]="Dung dịch NaOH.";
choices[59][3]="Dung dịch <img src=\"image/181.png\" style=\"vertical-align: -8px\" />.";
answers[59]=3;
itType[60]=2;
textArr[60]="Thủy phân hoàn toàn 60 gam hỗn hợp hai đipeptit thu được 63,6 gam hỗn hợp X gồm các amino axit (các amino axit chỉ có một nhóm amino và một nhóm cacbonyl trong phân tử). Nếu cho <img src=\"image/182.png\" style=\"vertical-align: -17px\" /> hỗn hợp X tác dụng với dung dịch HCl (dư), cô cạn cẩn thận dung dịch, thì lượng muối khan thu được là";
choices[60]=new Array();
choices[60][0]="7,09 gam.";
choices[60][1]="16,30 gam.";
choices[60][2]="8,15 gam.";
choices[60][3]="7,82 gam.";
answers[60]=3;
itType[61]=2;
textArr[61]="Cho sơ đồ phản ứng: <img src=\"image/183.png\" style=\"vertical-align: -8px\" /><br>Y và Z lần lượt dùng để chế tạo vật liệu polime nào sau đây?";
choices[61]=new Array();
choices[61][0]="Tơ capron và cao su buna.";
choices[61][1]="Tơ nilon-6,6 và cao su cloropren.";
choices[61][2]="Tơ olon và cao su buna-N.";
choices[61][3]="Tơ nitron và cao su buna-S.";
answers[61]=2;
itType[62]=2;
textArr[62]="Hòa tan hỗn hợp bột gồm m gam Cu và 4,64 gam <img src=\"image/184.png\" style=\"vertical-align: -8px\" /> vào dung dịch <img src=\"image/185.png\" style=\"vertical-align: -8px\" /> (loãng, rất dư), sau khi các phản ứng kết thúc chỉ thu được dung dịch X. Dung dịch X làm mất màu vừa đủ 100 ml dung dịch <img src=\"image/186.png\" style=\"vertical-align: -8px\" /> 0,1M. Giá trị của m là";
choices[62]=new Array();
choices[62][0]="0,96.";
choices[62][1]="1,24.";
choices[62][2]="0,64.";
choices[62][3]="3,2.";
answers[62]=0;
itType[63]=2;
textArr[63]="Hiện tượng xảy ra khi nhỏ vài giọt dung dịch <img src=\"image/187.png\" style=\"vertical-align: -8px\" /> vào dung dịch <img src=\"image/188.png\" style=\"vertical-align: -8px\" /> là:";
choices[63]=new Array();
choices[63][0]="Dung dịch chuyển từ màu vàng sang màu da cam.";
choices[63][1]="Dung dịch chuyển từ màu da cam sang màu vàng.";
choices[63][2]="Dung dịch chuyển từ màu vàng sang không màu.";
choices[63][3]="Dung dịch chuyển từ không vàng sang màu da cam.";
answers[63]=0;
itType[64]=2;
textArr[64]="Cho các phản ứng sau:<br>	<img src=\"image/189.png\" style=\"vertical-align: -8px\" /><br>	<img src=\"image/190.png\" style=\"vertical-align: -8px\" /><br>Dãy sắp xếp theo thứ tự tăng dần tính oxi hóa của các ion kim loại là:";
choices[64]=new Array();
choices[64][0]="<img src=\"image/191.png\" style=\"vertical-align: -5px\" />";
choices[64][1]="<img src=\"image/192.png\" style=\"vertical-align: -5px\" />";
choices[64][2]="<img src=\"image/193.png\" style=\"vertical-align: -5px\" />";
choices[64][3]="<img src=\"image/194.png\" style=\"vertical-align: -5px\" />";
answers[64]=0;
itType[65]=2;
textArr[65]="Đốt cháy hoàn toàn 0,11 gam một este X (tạo nên từ một axit cacboxylic đơn chức và một ancol đơn chức) thu được 0,22 gam <img src=\"image/195.png\" style=\"vertical-align: -8px\" /> và 0,99 gam <img src=\"image/196.png\" style=\"vertical-align: -8px\" />. Số este đồng phân của X là";
choices[65]=new Array();
choices[65][0]="2.";
choices[65][1]="5.";
choices[65][2]="4.";
choices[65][3]="6.";
answers[65]=2;
itType[66]=2;
textArr[66]="Dung dịch X gồm <img src=\"image/197.png\" style=\"vertical-align: -8px\" /> 1M (<img src=\"image/198.png\" style=\"vertical-align: -8px\" /> = 1,75.<img src=\"image/199.png\" style=\"vertical-align: -5px\" />) và HCl 0,001M. Giá trị pH của dung dịch X là";
choices[66]=new Array();
choices[66][0]="2,33.";
choices[66][1]="2,55.";
choices[66][2]="1,77.";
choices[66][3]="2,43.";
answers[66]=0;
itType[67]=2;
textArr[67]="Cho dãy chuyển hóa sau: <img src=\"image/200.png\" style=\"vertical-align: -15px\" /> (trong đó X, Y, Z là sản phẩm chính).<br>Tên gọi của Y, Z lần lượt là";
choices[67]=new Array();
choices[67][0]="benzylbromua và toluen.";
choices[67][1]="2-brom-1-phenylbenzen và stiren.";
choices[67][2]="1-brom-1-phenyletan và stiren.";
choices[67][3]="1-brom-2-phenyletan và stiren.";
answers[67]=2;
