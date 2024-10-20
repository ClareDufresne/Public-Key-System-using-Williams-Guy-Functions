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