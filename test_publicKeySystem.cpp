#include "gtest/gtest.h"
#include "publicKeySystem.h"
#include "gmp.h"
#include "gmpxx.h"
#include <boost/multiprecision/gmp.hpp>

using namespace std;
using namespace boost::multiprecision;

mpz_int Wa[4], Wb[4];       //representing {Lm, Km, Lm+1, Km+1}
mpz_int max1, max2;         //representing the number of times the algorithm is to be repeated
mpz_int P1, P2, p;
const mpz_int Q = 1;

TEST(testValidInput, Valid)
{
    EXPECT_TRUE(validInput(8, 27, 59, 1, 12, 35)); 
    EXPECT_TRUE(validInput(8, 27, 59, 1, 14, 44));
}
TEST(testValidInput, invalidInitialValues)
{
    EXPECT_FALSE(validInput(0, 27, 59, 1, 12, 35));
    EXPECT_FALSE(validInput(8, 27, 59, 1, 0, 35));
    EXPECT_FALSE(validInput(8, 27, 59, 1, 12, 0));
    EXPECT_FALSE(validInput(13, 27, 59, 1, 12, 35));
    EXPECT_FALSE(validInput(59, 27, 59, 1, 12, 35));
}
TEST(testValidInput, invalidGCD)
{
    EXPECT_FALSE(validInput(4, 26, 59, 1, 12, 35));
    EXPECT_FALSE(validInput(8, 30, 59, 1, 12, 35));
}
TEST(testValidInput, invalidLegendre)
{
    EXPECT_FALSE(validInput(4, 15, 59, 1, 12, 35)); 
    EXPECT_FALSE(validInput(12, 17, 59, 1, 12, 35)); 
}

TEST(testPublicKey, smallNumbers)
{
    P1 = 8;
    P2 = 15;
    p = 64853;
    max1 = 17;
    max2 = 34;
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2)); 
}
TEST(testPublicKey, 64bit)
{
    P1 = 525743914283904422;
    P2 = 32142304932421;
    p.assign("17812912950474366349");
    max1 = 57238957328521;
    max2 = 994325893258231;
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}
TEST(testPublicKey, 128bit)
{
    P1.assign("4239045195782701753210358302");
    P2.assign("537485967348673897638974290761");
    p.assign("255381622452996600686022602090624095303");
    max1.assign("957398245723987589237582653242");
    max2.assign("131242273184719845681957893256253411");
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}
TEST(testPublicKey, 256bit)
{
    P1.assign("5273895789237589723857107589023758623807238904678923689205230682376802736834");
    P2.assign("42309482098490283905723895689236891284783926529589327569283323242534636373");
    p.assign("76093268910939833207416254342638627432772080514920302210010842318464885741913");
    max1.assign("637496872917690874026206782746072876894728967892768029238457839238473825");
    max2.assign("7492875823652075836720687290768268239078927589364892097628689200927848488");
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}
TEST(testPublicKey, 512bit)
{
    P1.assign("567375285680295728365298095832753265726287627878979878917486124672354623546725786168969823657823567823325632876592758923758923283569826532785973772");
    P2.assign("2390537295789268926895623897532023984092385975728347532645263478325689376036809348690347690378963275643674672357823658937589263895627313221");
    p.assign("10344020500438634656137607001517581563698208526663715098454468692485706875191872406184968678260355826602311334532605253804885576157991433609810953907435319");
    max1.assign("2547349826529384678923476829347689432768937468903276823486743829769827849276842768234768236423463427068327648327684397689376834653275892532335");
    max2.assign("935829578923652165872637856472386578236576327856372465726982838328389235892769368394698759283957982658926953683785798237292930482075283582365629784327");
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}
TEST(testPublicKey, 1024bit)
{
    P1.assign("56418753257185731982056138927538902175893217859078392165326573289798327589327856478326532789743897489278953278956785642378653892758920375890289085239085397689432643207834728908205489327589436589432657723897985327582758924389564329872389574837589320768237292765893247689023768972343789246664");
    P2.assign("134971148111758658632326605820042564632637753389129741629994459802383702552542572361093954740865216871489302961912595074647371590047620604067472958159652957852649255010373582936775613855322609858590895730128612163739049213960324743399306310469941207325171489290140425740519018650402216020568397188231333841129");
    p.assign("148920661693909538424062448786695123110263212398881139781223818665891230787297156972720696964774370513198998479946769535044330467809538945294437059277486716890838558909840788611503590307275583660039991227602094961262393902038684547684088395682833001383785411109109778678829847954970925814883341895552042104207");
    max1.assign("146456220246702845237205805112150620425878498959173799980329055736701124378101868620268492661277837599170630789093309938496961658013764225239138231864297726026009880049260955228193982207729419600402155142538405519386394670723458535657679869708800654446029690424774501520886027308205953554935042197428367897963");
    max2.assign("138959306175530157912293525451450762025343910856298153662987089703712528558070630310638849055723340543109786637138523155756221076651640189871390651417612796587251131447500185281011997358802368603239253570443689613979049411062326320090489347737339997209039088761959789090670981174707230584486823624596091077289");
    //cout << mpz_probab_prime_p(p.backend().data(), 50) << endl;
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}
TEST(testPublicKey, 2048bit)
{
    P1.assign("28008532030697149532250837190720218199301245497977807420566722242429463797189451079491742246601301580413372148447341356420843883750600777823786293574313464355532100045453213724247617708255679462893099066145209170195159904986519669847657584504433037672399972208997500501875926881295035877235215654293812041599254398017989880504889128541971709042393038464702364263039212614033169158453717702170944211072239732421008480377675197315437204541116350703261169643669915258297203621673073883042313076825961642297802151968390933452179161350958940888022041880832423786989082072132998172280089076065532179167921140086162104226642");
    P2.assign("27077504767070849968508626962986345952937445392781970975424531545737950057250950950238827574206887539419130517582749422753442685805279331724079377832018454416160936917961936906568387403748019558736656246666665140076882049348144289096363515031743113527668240711045159391581688755286075618531197674111176760448368329676799746196116071086312395887593796758312560001733598433085263806323124606683122397356438982443810256878600269847640910724895064407533993510724543835520681956863526440896107232925061524838286167978911961127655244067096538803786813634944247634682363487876741797479090179989715253875867242351877205835087");
    p.assign("27492384904342374421405271721341915599427427553029698595667787591874625822737769740414933296436937250261349974011941992883723088138388463370835969291716256126736539099553796207083289045657702931162106049170166719627876327595455093419642072957515601163015943016784449808479334457411665845938429850861573021819323613425500970303428353659367258885463188970212372638176745944244376073537729504659230609447028597037844375770741043766898877346189001599948859206102342109464780827998045388446281375192679407404769849594395532476766343468319815781310666703504745284191836657489044454328626262580801030990366776226263197609799");
    max1.assign("663277741237110755091473803483842314808178572630920148155578720417848263771197331304442857510977426277993821565582136514184079942251621574692421445991157362961470673279186047942539925264235052916597907222212638403014461380943524287293097037341871405635312828508207063504515736272588628834126489709454577657343370438827780328595427975964738808108724526299316326869955759098300965710975019239964878446038933546010674863900903974132926057583785414482178523898747134942504546537932292670072411200622584037729626126155492374736636255167216468632230386898897424014424001061015200930889517960373852984602913757621346384927");
    max2.assign("18386184325826327627709647697993088745482389347733498669170052253402172313669349336434417699442931190745428597830525604062802542439577112599300508729424879735543841485766149336961462572456135614732972696036140197066257322318020864239361204051164626517005063994587033191298539125012128503693149205741942772165694213876906253452655218472479127521255335314145619776329294605000087813305216032113253534402461281261733948281183718163019740482057711797683182156342561132511672229997339481662743804403385676758658085565618302479515332281531622024759538209732912965354119102411666079749499433408543920265114697429523589770949");
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}
TEST(testPublicKey, 4096bit)
{
    P1.assign("1022410458297672702754011958807427560482745258118978467454761789657520711748654769740992317359845255499093040567820023186865246784239862920090468598011408337420726715647191068370022276641795085131387105360920665786796102236533774822971225847291509323605357445116217856109917494414692795689636464052820365355154992119002976849078871812993300226461854689883512258772043882672877915065726974069323573704339091957426537952234377887463438397602237471218450678229320371444979216647201813445210942278526575395171999055951173024450455121240253099812924167096168549015698210605272813977468615209809374282790289108069870874363152657228973540738175193071146899192176250314226121246993720090341891656686674467397618856443403701419269640789980901296521774691182925796365290797927804051199156583424122494516884649067878625894957380314755684249188678045235594748514662343507603915655345039623284110214372782298842631270244406744859535634485946052049487325120040063571756534675399584657103915961132509060668931755563807292197732973416562840423832076663892851740928921337759361068862488890356776719227689164229928658429641350458747827007799932786630254729631756720438797669808979797478684431372310361858255283594596502669932194845736791916858543125072");
    P2.assign("80280964463841474722257694890431918267901847122154949546503137419792630009458592534492418791009239514646401683783836319197052317959115469595448870907509643234183836592552276650577220720213477091685883698307305668258125129136623669899300468346860213191561821562906062389875934324052382871970357497013666761761726439082336270638140225376761432591798967524373296388676427186586628201737605613475388055842516138001986904985930947439548475591547564043937747604687895038792516559013034812443706522190918458074754783074826644018541701031490128493156338645993074661678561203877791169603719848369213568420285519338024370262413373854032205617829579153331968946427847593329933212998650873602264193339286691375432952074848011105727548110626073614030250303232558950110891658512423041364662895208264671761456906727674698369347454312179574500972781067250949786395262594233493035472198600569755162519574992115177315880852255110452268540862029924251610861326548332265864714074022560148022470480595963231545768042327136152191549456280746221739830992611614596465396720417020313228544841787220533515319915444083458744078642066275722542378528111756638963523845275123573522038817023904798978240318759925992690934782002462498449102901213615499327027372799");
    p.assign("841096659250897829882925416048540423467653683849169019785829254863190901856648909390454460824266952855379458216042215922517330434976098383008607563301899171760672201332604432792923436750514970904509831969147357164893126833977168868396193555611951667944568353526514655381420953715428346340933635713389068725174991393636944944255306855824136726387767144176501521875262733745654165131968394313844699742269368789126254935764505950630435699136125867748285733015958256742146075494409386077797460197761569303078347376915924794092439317627997013687170395458791803027888901328211652166515339545494744895869215500345231329036560626983012799802233853680583390413004476970581739772427967967597811315100918821773074765535700788815509672954773812130239590004294679407161627008154864821633350735528869160197089565359777260749625230259607514966749902102897896562373605040053453981069684468740113617761287962656069775845191781601126290325360548246587474970672005432334537365738525190439343711889997557156091493042012352513234189732996139493263410255095792940541199449549359844229391077859410136726348662058596659729353431220419067879072821499554797667916720823462328148402855100708872902715025738228607613342609751314018439403649110735235983155151773");
    max1.assign("538583852960504435390247597761153966108305636978519775220601209270696649547214733034056892630248498158719892138181697405201475950206902649358926567264103355119950736277692916034699124139084421953178008040917140560580352382799245459891677981490968011357587138376381615573730339443302572008185409543866047683372364645804950926417945588674707994215466291210900289585008833854298783203558873023463800293283911424452705240334876543902942395228247677236915718108640842611833746683045688634690828805719283853658616198903961817735471767783625788133992646921157215957359618553584487789144493882980497116649888884914157485912216726216647494877094615773060121381425993996990180745579747161121623562800715543613981006379087392503679631850739415118376564592718052953595420302981743899184106032562801800321953942863657575254059121457650754257963019828870691568512966076895575121831616807155756337348600149732545923613613151808468981937937826233261589022043998733440083580404743674888232993659472622095902918586466706336938021763268758486450045902860859388037902667423511610240252287057502724470199325941748611188965282328297710880382149488263439839746626900586153565369456646636401764562553143080941495802527754857099874843275915572653242");
    max2.assign("1319585829676013022890615390061786696477764317765838398605883454975074474494853545524863971135165830075435711534977331656674175745776833819432031385727023610817041677574411231073904304954866728363944745234610695297156404517269991570150648385414975155042791146883698933433457714156737081661221102758509993898595244861222261505385838529605044353902475977611539661083056369785197752206012092706966495472147330340568926302484981587198921381816974052014759502069026493589265672641033551199507362776929160346991241390844219531780080409171405605115809789840383839201731484239675849056524112226864701964411602157194655237871920591720499270164812240412920245634213348659041228162219098830598385911532598035238279924545989167798149096801135758713837638161557373033944330257200818540954386604768337236464580495092641794558867470799421546629121090028958500883385429878320355887302346380029328391142445270524033487654390294239522824767723691571810864084261183374668304568863469082880571928385365861619890396181773524227318471984568195789325625115809789840383839201731484239675849056524112226864701964411602157194655237871920591720499270164812240412920245634213348659041228162219098830598385911532557234985783246392893411");
    ASSERT_TRUE(validInput(P1, P2, p, Q, max1, max2));
    EXPECT_TRUE(publicKey(Wa, Wb, P1, P2, Q, p, max1, max2));  
}