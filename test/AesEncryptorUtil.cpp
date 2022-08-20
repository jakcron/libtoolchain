#include "AesEncryptorUtil.h"

#include <tc/cli/FormatUtil.h>

void AesEncryptorUtil::generateAesTestVectors_Nist(std::vector<AesEncryptorUtil::TestVector>& test_list, size_t key_size)
{
	AesEncryptorUtil::TestVector tmp;

	if (key_size == 128)
	{
		test_list.clear();

		// Variable Key Known Answer Tests
		// taken from "ecb_vk.txt" from https://csrc.nist.gov/archive/aes/rijndael/rijndael-vals.zip
		tmp.plaintext = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000000");

		tmp.test_name = "Variable Key Known Answer Test 1";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("80000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0EDD33D3C621E546455BD8BA1418BEC8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 2";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("40000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C0CC0C5DA5BD63ACD44A80774FAD5222");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 3";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("20000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2F0B4B71BC77851B9CA56D42EB8FF080");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 4";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("10000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6B1E2FFFE8A114009D8FE22F6DB5F876");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 5";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("08000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9AA042C315F94CBB97B62202F83358F5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 6";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("04000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DBE01DE67E346A800C4C4B4880311DE4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 7";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("02000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C117D2238D53836ACD92DDCDB85D6A21");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 8";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("01000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DC0ED85DF9611ABB7249CDD168C5467E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 9";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00800000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("807D678FFF1F56FA92DE3381904842F2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 10";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00400000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0E53B3FCAD8E4B130EF73AEB957FB402");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 11";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00200000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("969FFD3B7C35439417E7BDE923035D65");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 12";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00100000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A99B512C19CA56070491166A1503BF15");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 13";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00080000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6E9985252126EE344D26AE369D2327E3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 14";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00040000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B85F4809F904C275491FCDCD1610387E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 15";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00020000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ED365B8D7D20C1F5D53FB94DD211DF7B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 16";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00010000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B3A575E86A8DB4A7135D604C43304896");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 17";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00008000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("89704BCB8E69F846259EB0ACCBC7F8A2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 18";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00004000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C56EE7C92197861F10D7A92B90882055");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 19";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00002000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("92F296F6846E0EAF9422A5A24A08B069");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 20";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00001000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E67E32BB8F11DEB8699318BEE9E91A60");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 21";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000800000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B08EEF85EAF626DD91B65C4C3A97D92B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 22";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000400000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("661083A6ADDCE79BB4E0859AB5538013");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 23";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000200000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("55DFE2941E0EB10AFC0B333BD34DE1FE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 24";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000100000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6BFE5945E715C9662609770F8846087A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 25";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000080000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("79848E9C30C2F8CDA8B325F7FED2B139");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 26";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000040000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7A713A53B99FEF34AC04DEEF80965BD0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 27";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000020000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("18144A2B46620D32C3C32CE52D49257F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 28";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000010000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("872E827C70887C80749F7B8BB1847C7E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 29";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000008000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6B86C6A4FE6A60C59B1A3102F8DE49F3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 30";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000004000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9848BB3DFDF6F532F094679A4C231A20");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 31";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000002000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("925AD528E852E329B2091CD3F1C2BCEE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 32";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000001000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("80DF436544B0DD596722E46792A40CD8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 33";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000800000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("525DAF18F93E83E1E74BBBDDE4263BBA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 34";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000400000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F65C9D2EE485D24701FFA3313B9D5BE6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 35";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000200000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E4FC8D8BCA06425BDF94AFA40FCC14BA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 36";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000100000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A53F0A5CA1E4E6440BB975FF320DE6F8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 37";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000080000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D55313B9394080462E87E02899B553F0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 38";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000040000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("34A71D761F71BCD344384C7F97D27906");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 39";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000020000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("233F3D819599612EBC89580245C996A8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 40";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000010000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B4F1374E5268DBCB676E447529E53F89");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 41";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000008000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0816BD27861D2BA891D1044E39951E96");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 42";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000004000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F3BE9EA3F10C73CA64FDE5DB13A951D1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 43";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000002000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2448086A8106FBD03048DDF857D3F1C8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 44";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000001000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("670756E65BEC8B68F03D77CDCDCE7B91");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 45";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000800000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EF968CF0D36FD6C6EFFD225F6FB44CA9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 46";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000400000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2E8767157922E3826DDCEC1B0CC1E105");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 47";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000200000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("78CE7EEC670E45A967BAB17E26A1AD36");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 48";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000100000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3C5CEE825655F098F6E81A2F417DA3FB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 49";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000080000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("67BFDB431DCE1292200BC6F5207ADB12");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 50";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000040000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7540FD38E447C0779228548747843A6F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 51";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000020000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B85E513301F8A936EA9EC8A21A85B5E6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 52";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000010000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("04C67DBF16C11427D507A455DE2C9BC5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 53";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000008000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("03F75EB8959E55079CFFB4FF149A37B6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 54";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000004000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("74550287F666C63BB9BC7838433434B0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 55";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000002000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7D537200195EBC3AEFD1EAAB1C385221");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 56";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000001000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CE24E4D40C68A82B535CBD3C8E21652A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 57";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000800000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AB20072405AA8FC40265C6F1F3DC8BC0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 58";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000400000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6CFD2CF688F566B093F67B9B3839E80A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 59";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000200000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BD95977E6B7239D407A012C5544BF584");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 60";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000100000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DF9C0130AC77E7C72C997F587B46DBE0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 61";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000080000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7F1B82CADC53A648798945B34EFEFF2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 62";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000040000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("932C6DBF69255CF13EDCDB72233ACEA3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 63";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000020000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5C76002BC7206560EFE550C80B8F12CC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 64";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000010000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F6B7BDD1CAEEBAB574683893C4475484");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 65";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000008000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A920E37CC6DC6B31DA8C0169569F5034");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 66";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000004000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("919380ECD9C778BC513148B0C28D65FD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 67";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000002000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EE67308DD3F2D9E6C2170755E5784BE1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 68";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000001000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3CC73E53B85609023A05E149B223AE09");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 69";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000800000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("983E8AF7CF05EBB28D71EB841C9406E6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 70";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000400000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0F3099B2D31FA5299EE5BF43193287FC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 71";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000200000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B763D84F38C27FE6931DCEB6715D4DB6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 72";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000100000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5AE3C9B0E3CC29C0C61565CD01F8A248");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 73";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000080000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F58083572CD90981958565D48D2DEE25");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 74";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000040000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7E6255EEF8F70C0EF10337AAB1CCCEF8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 75";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000020000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AAD4BAC34DB22821841CE2F631961902");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 76";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000010000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D7431C0409BB1441BA9C6858DC7D4E81");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 77";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000008000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EF9298C65E339F6E801A59C626456993");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 78";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000004000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("53FE29F68FF541ABC3F0EF3350B72F7E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 79";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000002000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F6BBA5C10DB02529E2C2DA3FB582CC14");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 80";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000001000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E4239AA37FC531A386DAD1126FC0E9CD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 81";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000800000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8F7758F857D15BBE7BFD0E416404C365");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 82";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000400000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D273EB57C687BCD1B4EA7218A509E7B8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 83";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000200000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("65D64F8D76E8B3423FA25C4EB58A210A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 84";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000100000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("623D802B4EC450D66A16625702FCDBE0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 85";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000080000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7496460CB28E5791BAEAF9B68FB00022");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 86";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000040000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("34EA600F18BB0694B41681A49D510C1D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 87";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000020000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5F8FF0D47D5766D29B5D6E8F46423BD8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 88";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000010000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("225F9286C5928BF09F84D3F93F541959");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 89";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000008000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B21E90D25DF383416A5F072CEBEB1FFB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 90";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000004000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4AEFCDA089318125453EB9E8EB5E492E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 91";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000002000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4D3E75C6CD40EC4869BC85158591ADB8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 92";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000001000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("63A8B904405436A1B99D7751866771B7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 93";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000800000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("64F0DAAE47529199792EAE172BA53293");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 94";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000400000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C3EEF84BEA18225D515A8C852A9047EE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 95";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000200000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A44AC422B47D47B81AF73B3E9AC9596E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 96";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000100000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D16E04A8FBC435094F8D53ADF25F5084");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 97";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000080000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EF13DC34BAB03E124EEAD8B6BF44B532");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 98";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000040000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D94799075C24DCC067AF0D392049250D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 99";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000020000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("14F431771EDDCE4764C21A2254B5E3C8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 100";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000010000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7039329F36F2ED682B02991F28D64679");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 101";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000008000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("124EE24EDE5551639DB8B8B941F6141D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 102";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000004000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C2852879A34D5184E478EC918B993FEE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 103";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000002000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("86A806A3525B93E432053C9AB5ABBEDF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 104";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000001000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C1609BF5A4F07E37C17A36366EC23ECC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 105";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000800000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7E81E7CB92159A51FFCEA331B1E8EA53");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 106";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000400000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("37A7BE002856C5A59A6E03EAFCE7729A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 107";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000200000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BDF98A5A4F91E890C9A1D1E5FAAB138F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 108";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000100000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4E96ACB66E051F2BC739CC3D3E34A26B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 109";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000080000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EE996CDD120EB86E21ECFA49E8E1FCF1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 110";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000040000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("61B9E6B579DBF6070C351A1440DD85FF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 111";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000020000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AC369E484316440B40DFC83AA96E28E7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 112";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000010000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0A2D16DE985C76D45C579C1159413BBE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 113";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000008000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DA3FDC38DA1D374FA4802CDA1A1C6B0F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 114";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000004000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B842523D4C41C2211AFE43A5800ADCE3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 115";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000002000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9E2CDA90D8E992DBA6C73D8229567192");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 116";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000001000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D49583B781D9E20F5BE101415957FC49");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 117";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000800");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EF09DA5C12B376E458B9B8670032498E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 118";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000400");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A96BE0463DA774461A5E1D5A9DD1AC10");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 119";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000200");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("32CEE3341060790D2D4B1362EF397090");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 120";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000100");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("21CEA416A3D3359D2C4D58FB6A035F06");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 121";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000080");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("172AEAB3D507678ECAF455C12587ADB7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 122";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000040");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B6F897941EF8EBFF9FE80A567EF38478");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 123";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000020");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A9723259D94A7DC662FB0C782CA3F1DD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 124";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000010");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2F91C984B9A4839F30001B9F430493B4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 125";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000008");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0472406345A610B048CB99EE0EF3FA0F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 126";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000004");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F5F39086646F8C05ED16EFA4B617957C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 127";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000002");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("26D50F485A30408D5AF47A5736292450");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 128";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000001");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0545AAD56DA2A97C3663D1432A3D1C84");
		test_list.push_back(tmp);
	}
	else if (key_size == 192)
	{
		test_list.clear();

		// Variable Key Known Answer Tests
		// taken from "ecb_vk.txt" from https://csrc.nist.gov/archive/aes/rijndael/rijndael-vals.zip
		tmp.plaintext = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000000");

		tmp.test_name = "Variable Key Known Answer Test 1";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("800000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DE885DC87F5A92594082D02CC1E1B42C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 2";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("400000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C749194F94673F9DD2AA1932849630C1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 3";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("200000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0CEF643313912934D310297B90F56ECC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 4";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("100000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C4495D39D4A553B225FBA02A7B1B87E1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 5";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("080000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("636D10B1A0BCAB541D680A7970ADC830");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 6";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("040000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("07CF045786BD6AFCC147D99E45A901A7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 7";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("020000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6A8E3F425A7599348F95398448827976");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 8";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("010000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5518276836148A00D91089A20D8BFF57");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 9";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("008000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F267E07B5E87E3BC20B969C61D4FCB06");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 10";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("004000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5A1CDE69571D401BFCD20DEBADA2212C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 11";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("002000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("70A9057263254701D12ADD7D74CD509E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 12";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("001000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("35713A7E108031279388A33A0FE2E190");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 13";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000800000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E74EDE82B1254714F0C7B4B243108655");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 14";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000400000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("39272E3100FAA37B55B862320D1B3EB3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 15";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000200000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6D6E24C659FC5AEF712F77BCA19C9DD0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 16";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000100000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("76D18212F972370D3CC2C6C372C6CF2F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 17";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000080000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B21A1F0BAE39E55C7594ED570A7783EA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 18";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000040000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("77DE202111895AC48DD1C974B358B458");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 19";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000020000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("67810B311969012AAF7B504FFAF39FD1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 20";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000010000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C22EA2344D3E9417A6BA07843E713AEA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 21";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000008000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C79CAF4B97BEE0BD0630AB354539D653");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 22";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000004000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("135FD1AF761D9AE23DF4AA6B86760DB4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 23";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000002000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D4659D0B06ACD4D56AB8D11A16FD83B9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 24";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000001000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F7D270028FC188E4E4F35A4AAA25D4D4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 25";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000800000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("345CAE5A8C9620A9913D5473985852FF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 26";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000400000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4E8980ADDE60B0E42C0B287FEA41E729");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 27";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000200000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F11B6D74E1F15155633DC39743C1A527");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 28";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000100000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9C87916C0180064F9D3179C6F5DD8C35");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 29";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000080000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("71AB186BCAEA518E461D4F7FAD230E6A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 30";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000040000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C4A31BBC3DAAF742F9141C2A5001A49C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 31";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000020000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7C47B7B1D40F182A8928C8A55671D07");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 32";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000010000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8E17F294B28FA373C6249538868A7EEF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 33";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000008000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("754404096A5CBC08AF09491BE249141A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 34";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000004000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("101CB56E55F05D86369B6D1069204F0A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 35";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000002000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("73F19BB6604205C6EE227B9759791E41");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 36";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000001000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6270C0028F0D136C37A56B2CB64D24D6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 37";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000800000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A3BF7C2C38D1114A087ECF212E694346");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 38";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000400000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("49CABFF2CEF7D9F95F5EFB1F7A1A7DDE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 39";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000200000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EC7F8A47CC59B849469255AD49F62752");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 40";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000100000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("68FAE55A13EFAF9B07B3552A8A0DC9D1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 41";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000080000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("211E6B19C69FAEF481F64F24099CDA65");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 42";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000040000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DBB918C75BC5732416F79FB0C8EE4C5C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 43";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000020000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("98D494E5D963A6C8B92536D3EC35E3FD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 44";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000010000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C9A873404D403D6F074190851D67781A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 45";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000008000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("073AEF4A7C77D921928CB0DD9D27CAE7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 46";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000004000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("89BDE25CEE36FDE769A10E52298CF90F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 47";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000002000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("26D0842D37EAD38557C65E0A5E5F122E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 48";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000001000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F8294BA375AF46B3F22905BBAFFAB107");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 49";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000800000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2AD63EB4D0D43813B979CF72B35BDB94");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 50";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000400000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7710C171EE0F4EFA39BE4C995180181D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 51";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000200000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C0CB2B40DBA7BE8C0698FAE1E4B80FF8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 52";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000100000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("97970E505194622FD955CA1B80B784E9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 53";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000080000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7CB1824B29F850900DF2CAD9CF04C1CF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 54";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000040000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FDF4F036BB988E42F2F62DE63FE19A64");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 55";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000020000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("08908CFE2C82606B2C15DF61B75CF3E2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 56";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000010000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B3AA689EF2D07FF365ACB9ADBA2AF07A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 57";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000008000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F2672CD8EAA3B98776660D0263656F5C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 58";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000004000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5BDEAC00E986687B9E1D94A0DA7BF452");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 59";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000002000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E6D57BD66EA1627363EE0C4B711B0B21");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 60";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000001000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("03730DD6ACB4AD9996A63BE7765EC06F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 61";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000800000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A470E361AA5437B2BE8586D2F78DE582");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 62";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000400000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7567FEEFA559911FD479670246B484E3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 63";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000200000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("29829DEA15A4E7A4C049045E7B106E29");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 64";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000100000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A407834C3D89D48A2CB7A152208FA4ED");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 65";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000080000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("68F948053F78FEF0D8F9FE7EF3A89819");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 66";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000040000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B605174CAB13AD8FE3B20DA3AE7B0234");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 67";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000020000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CCAB8F0AEBFF032893996D383CBFDBFA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 68";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000010000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AF14BB8428C9730B7DC17B6C1CBEBCC8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 69";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000008000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5A41A21332040877EB7B89E8E80D19FE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 70";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000004000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AC1BA52EFCDDE368B1596F2F0AD893A0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 71";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000002000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("41B890E31B9045E6ECDC1BC3F2DB9BCC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 72";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000001000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4D54A549728E55B19A23660424A0F146");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 73";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000800000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A917581F41C47C7DDCFFD5285E2D6A61");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 74";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000400000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("604DF24BA6099B93A7405A524D764FCB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 75";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000200000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("78D9D156F28B190E232D1B7AE7FC730A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 76";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000100000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5A12C39E442CD7F27B3CD77F5D029582");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 77";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000080000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FF2BF2F47CF7B0F28EE25AF95DBF790D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 78";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000040000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1863BB7D193BDA39DF090659EB8AE48B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 79";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000020000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("38178F2FB4CFCF31E87E1ABCDC023EB5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 80";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000010000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F5B13DC690CC0D541C6BA533023DC8C9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 81";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000008000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("48EC05238D7375D126DC9D08884D4827");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 82";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000004000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ACD0D81139691B310B92A6E377BACC87");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 83";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000002000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9A4AA43578B55CE9CC178F0D2E162C79");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 84";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000001000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("08AD94BC737DB3C87D49B9E01B720D81");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 85";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000800000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3BCFB2D5D210E8332900C5991D551A2A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 86";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000400000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C5F0C6B9397ACB29635CE1A0DA2D8D96");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 87";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000200000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("844A29EFC693E2FA9900F87FBF5DCD5F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 88";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000100000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5126A1C41051FEA158BE41200E1EA59D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 89";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000080000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("302123CA7B4F46D667FFFB0EB6AA7703");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 90";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000040000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A9D16BCE7DB5C024277709EE2A88D91A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 91";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000020000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F013C5EC123A26CFC34B598C992A996B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 92";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000010000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E38A825CD971A1D2E56FB1DBA248F2A8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 93";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000008000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6E701773C0311E0BD4C5A097406D22B3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 94";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000004000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("754262CEF0C64BE4C3E67C35ABE439F7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 95";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000002000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C9C2D4C47DF7D55CFA0EE5F1FE5070F4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 96";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000001000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6AB4BEA85B172573D8BD2D5F4329F13D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 97";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000800000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("11F03EF28E2CC9AE5165C587F7396C8C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 98";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000400000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0682F2EB1A68BAC7949922C630DD27FA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 99";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000200000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ABB0FEC0413D659AFE8E3DCF6BA873BB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 100";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000100000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FE86A32E19F805D6569B2EFADD9C92AA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 101";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000080000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E434E472275D1837D3D717F2EECC88C3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 102";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000040000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("74E57DCD12A21D26EF8ADAFA5E60469A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 103";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000020000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C275429D6DAD45DDD423FA63C816A9C1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 104";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000010000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7F6EC1A9AE729E86F7744AED4B8F4F07");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 105";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000008000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("48B5A71AB9292BD4F9E608EF102636B2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 106";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000004000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("076FB95D5F536C78CBED3181BCCF3CF1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 107";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000002000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BFA76BEA1E684FD3BF9256119EE0BC0F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 108";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000001000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7D395923D56577F3FF8670998F8C4A71");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 109";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000800000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BA02C986E529AC18A882C34BA389625F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 110";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000400000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3DFCF2D882AFE75D3A191193013A84B5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 111";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000200000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FAD1FDE1D0241784B63080D2C74D236C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 112";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000100000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7D6C80D39E41F007A14FB9CD2B2C15CD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 113";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000080000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7975F401FC10637BB33EA2DB058FF6EC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 114";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000040000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("657983865C55A818F02B7FCD52ED7E99");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 115";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000020000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B32BEB1776F9827FF4C3AC9997E84B20");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 116";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000010000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2AE2C7C374F0A41E3D46DBC3E66BB59F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 117";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000008000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4D835E4ABDD4BDC6B88316A6E931A07F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 118";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000004000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E07EFABFF1C353F7384EBB87B435A3F3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 119";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000002000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ED3088DC3FAF89AD87B4356FF1BB09C2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 120";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000001000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4324D01140C156FC898C2E32BA03FB05");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 121";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000800000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BE15D016FACB5BAFBC24FA9289132166");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 122";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000400000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AC9B7048EDB1ACF4D97A5B0B3F50884B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 123";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000200000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("448BECE1F86C7845DFA9A4BB2A016FB3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 124";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000100000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("10DD445E87686EB46EA9B1ABC49257F0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 125";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000080000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B7FCCF7659FA756D4B7303EEA6C07458");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 126";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000040000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("289117115CA3513BAA7640B1004872C2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 127";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000020000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("57CB42F7EE7186051F50B93FFA7B35BF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 128";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000010000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F2741BFBFB81663B9136802FB9C3126A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 129";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000008000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E32DDDC5C7398C096E3BD535B31DB5CE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 130";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000004000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("81D3C204E608AF9CC713EAEBCB72433F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 131";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000002000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D4DEEF4BFC36AAA579496E6935F8F98E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 132";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000001000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C356DB082B97802B038571C392C5C8F6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 133";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000800000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A3919ECD4861845F2527B77F06AC6A4E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 134";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000400000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A53858E17A2F802A20E40D44494FFDA0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 135";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000200000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5D989E122B78C758921EDBEEB827F0C0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 136";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000100000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4B1C0C8F9E7830CC3C4BE7BD226FA8DE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 137";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000080000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("82C40C5FD897FBCA7B899C70713573A1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 138";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000040000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ED13EE2D45E00F75CCDB51EA8E3E36AD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 139";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000020000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F121799EEFE8432423176A3CCF6462BB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 140";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000010000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4FA0C06F07997E98271DD86F7B355C50");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 141";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000008000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("849EB364B4E81D058649DC5B1BF029B9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 142";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000004000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F48F9E0DE8DE7AD944A207809335D9B1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 143";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000002000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E59E9205B5A81A4FD26DFCF308966022");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 144";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000001000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3A91A1BE14AAE9ED700BDF9D70018804");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 145";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000800000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8ABAD78DCB79A48D79070E7DA89664EC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 146";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000400000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B68377D98AAE6044938A7457F6C649D9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 147";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000200000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E4E1275C42F5F1B63D662C099D6CE33D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 148";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000100000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7DEF32A34C6BE668F17DA1BB193B06EF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 149";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000080000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("78B6000CC3D30CB3A74B68D0EDBD2B53");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 150";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000040000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0A47531DE88DD8AE5C23EAE4F7D1F2D5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 151";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000020000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("667B24E8000CF68231EC484581D922E5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 152";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000010000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("39DAA5EBD4AACAE130E9C33236C52024");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 153";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000008000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E3C88760B3CB21360668A63E55BB45D1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 154";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000004000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F131EE903C1CDB49D416866FD5D8DE51");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 155";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000002000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7A1916135B0447CF4033FC13047A583A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 156";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000001000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F7D55FB27991143DCDFA90DDF0424FCB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 157";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000800000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EA93E7D1CA1111DBD8F7EC111A848C0C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 158";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000400000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2A689E39DFD3CBCBE221326E95888779");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 159";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000200000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C1CE399CA762318AC2C40D1928B4C57D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 160";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000100000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D43FB6F2B2879C8BFAF0092DA2CA63ED");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 161";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000080000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("224563E617158DF97650AF5D130E78A5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 162";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000040000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6562FDF6833B7C4F7484AE6EBCC243DD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 163";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000020000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("93D58BA7BED22615D661D002885A7457");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 164";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000010000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9A0EF559003AD9E52D3E09ED3C1D3320");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 165";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000008000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("96BAF5A7DC6F3DD27EB4C717A85D261C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 166";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000004000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B8762E06884900E8452293190E19CCDB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 167";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000002000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("785416A22BD63CBABF4B1789355197D3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 168";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000001000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A0D20CE1489BAA69A3612DCE90F7ABF6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 169";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000800000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("700244E93DC94230CC607FFBA0E48F32");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 170";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000400000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("85329E476829F872A2B4A7E59F91FF2D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 171";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000200000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E4219B4935D988DB719B8B8B2B53D247");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 172";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000100000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6ACDD04FD13D4DB4409FE8DD13FD737B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 173";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000080000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9EB7A670AB59E15BE582378701C1EC14");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 174";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000040000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("29DF2D6935FE657763BC7A9F22D3D492");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 175";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000020000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("99303359D4A13AFDBE6C784028CE533A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 176";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000010000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FF5C70A6334545F33B9DBF7BEA0417CA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 177";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000008000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("289F58A17E4C50EDA4269EFB3DF55815");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 178";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000004000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EA35DCB416E9E1C2861D1682F062B5EB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 179";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000002000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3A47BF354BE775383C50B0C0A83E3A58");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 180";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000001000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BF6C1DC069FB95D05D43B01D8206D66B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 181";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000800");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("046D1D580D5898DA6595F32FD1F0C33D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 182";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000400");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5F57803B7B82A110F7E9855D6A546082");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 183";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000200");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("25336ECF34E7BE97862CDFF715FF05A8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 184";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000100");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("ACBAA2A943D8078022D693890E8C4FEF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 185";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000080");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3947597879F6B58E4E2F0DF825A83A38");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 186";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000040");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4EB8CC3335496130655BF3CA570A4FC0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 187";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000020");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BBDA7769AD1FDA425E18332D97868824");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 188";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000010");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5E7532D22DDB0829A29C868198397154");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 189";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000008");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E66DA67B630AB7AE3E682855E1A1698E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 190";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000004");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4D93800F671B48559A64D1EA030A590A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 191";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000002");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F33159FCC7D9AE30C062CD3B322AC764");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 192";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("000000000000000000000000000000000000000000000001");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8BAE4EFB70D33A9792EEA9BE70889D72");
		test_list.push_back(tmp);
	}
	else if (key_size == 256)
	{
		test_list.clear();

		// Variable Key Known Answer Tests
		// taken from "ecb_vk.txt" from https://csrc.nist.gov/archive/aes/rijndael/rijndael-vals.zip
		tmp.plaintext = tc::cli::FormatUtil::hexStringToBytes("00000000000000000000000000000000");

		tmp.test_name = "Variable Key Known Answer Test 1";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("8000000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E35A6DCB19B201A01EBCFA8AA22B5759");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 2";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("4000000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5075C2405B76F22F553488CAE47CE90B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 3";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("2000000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("49DF95D844A0145A7DE01C91793302D3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 4";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("1000000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7396D778E940B8418A86120E5F421FE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 5";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0800000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("05F535C36FCEDE4657BE37F4087DB1EF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 6";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0400000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D0C1DDDD10DA777C68AB36AF51F2C204");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 7";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0200000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1C55FB811B5C6464C4E5DE1535A75514");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 8";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0100000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("52917F3AE957D5230D3A2AF57C7B5A71");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 9";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0080000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C6E3D5501752DD5E9AEF086D6B45D705");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 10";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0040000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A24A9C7AF1D9B1E17E1C9A3E711B3FA7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 11";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0020000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B881ECA724A6D43DBC6B96F6F59A0D20");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 12";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0010000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EC524D9A24DFFF2A9639879B83B8E137");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 13";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0008000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("34C4F345F5466215A037F443635D6F75");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 14";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0004000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5BA5055BEDB8895F672E29F2EB5A355D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 15";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0002000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B3F692AA3A435259EBBEF9B51AD1E08D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 16";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0001000000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("414FEB4376F2C64A5D2FBB2ED531BA7D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 17";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000800000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A20D519E3BCA3303F07E81719F61605E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 18";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000400000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A08D10E520AF811F45BD60A2DC0DC4B1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 19";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000200000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B06893A8C563C430E6F3858826EFBBE4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 20";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000100000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FFEE26AE2D3929C6BD9C6BEDFF84409");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 21";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000080000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4D0F5E906ED77801FC0EF53EDC5F9E2B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 22";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000040000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8B6EC00119AD8B026DCE56EA7DEFE930");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 23";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000020000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("69026591D43363EE9D83B5007F0B484E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 24";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000010000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("27135D86950C6A2F86872706279A4761");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 25";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000008000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("35E6DB8723F281DA410C3AC8535ED77C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 26";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000004000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("57427CF214B8C28E4BBF487CCB8D0E09");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 27";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000002000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6DF01BF56E5131AC87F96E99CAB86367");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 28";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000001000000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3856C5B55790B768BBF7D43031579BCF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 29";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000800000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1E6ED8FB7C15BC4D2F63BA7037ED44D0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 30";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000400000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E1B2ED6CD8D93D455534E401156D4BCF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 31";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000200000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EFBCCA5BDFDAD10E875F02336212CE36");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 32";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000100000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0B777F02FD18DCE2646DCFE868DFAFAD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 33";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000080000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C8A104B5693D1B14F5BF1F10100BF508");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 34";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000040000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4CCE6615244AFCB38408FECE219962EA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 35";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000020000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F99E7845D3A255B394C9C050CBA258B1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 36";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000010000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B4AFBB787F9BCFB7B55FDF447F611295");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 37";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000008000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AE1C426A697FAF2808B7EF6ADDB5C020");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 38";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000004000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7572F92811A85B9BDD38DEAD9945BCAE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 39";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000002000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("71BC7AA46E43FB95A181527D9F6A360F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 40";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000001000000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5542EF2923066F1EC8F546DD0D8E7CA8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 41";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000800000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6B92317C7D623790B748FDD7EFC42422");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 42";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000400000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FE7C097E899C71EF045360F8D6C25CF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 43";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000200000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4ECE7EE107D0264D04693151C25B9DF6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 44";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000100000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FD6AE687CBFCA9E301045888D3BB9605");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 45";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000080000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("476B579C8556C7254424902CC1D6D36E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 46";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000040000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4133CBCDFDD6B8860A1FC18665D6D71B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 47";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000020000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3B36EC2664798C108B816812C65DFDC7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 48";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000010000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("364E20A234FEA385D48DC5A09C9E70CF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 49";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000008000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4A4BA25969DE3F5EE5642C71AAD0EFD1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 50";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000004000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E42CBAAE43297F67A76C1C501BB79E36");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 51";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000002000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("23CEDEDA4C15B4C037E8C61492217937");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 52";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000001000000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A1719147A1F4A1A1180BD16E8593DCDE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 53";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000800000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AB82337E9FB0EC60D1F25A1D0014192C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 54";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000400000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("74BF2D8FC5A8388DF1A3A4D7D33FC164");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 55";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000200000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D5B493317E6FBC6FFFD664B3C491368A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 56";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000100000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BA767381586DA56A2A8D503D5F7ADA0B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 57";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000080000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E8E6BC57DFE9CCADB0DECABF4E5CF91F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 58";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000040000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3C8E5A5CDC9CEED90815D1F84BB2998C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 59";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000020000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("283843020BA38F056001B2FD585F7CC9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 60";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000010000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D8ADC7426F623ECE8741A70621D28870");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 61";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000008000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D7C5C215592D06F00E6A80DA69A28EA9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 62";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000004000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("52CF6FA433C3C870CAC70190358F7F16");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 63";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000002000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F63D442A584DA71786ADEC9F3346DF75");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 64";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000001000000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("549078F4B0CA7079B45F9A5ADAFAFD99");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 65";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000800000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F2A5986EE4E9984BE2BAFB79EA8152FA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 66";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000400000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8A74535017B4DB2776668A1FAE64384C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 67";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000200000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E613342F57A97FD95DC088711A5D0ECD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 68";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000100000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3FFAEBF6B22CF1DC82AE17CD48175B01");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 69";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000080000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BAFD52EFA15C248CCBF9757735E6B1CE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 70";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000040000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7AF94BC018D9DDD4539D2DD1C6F4000F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 71";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000020000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FE177AD61CA0FDB281086FBA8FE76803");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 72";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000010000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("74DBEA15E2E9285BAD163D7D534251B6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 73";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000008000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("23DD21331B3A92F200FE56FF050FFE74");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 74";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000004000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A69C5AA34AB20A858CAFA766EACED6D8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 75";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000002000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3F72BB4DF2A4F941A4A09CB78F04B97A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 76";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000001000000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("72CC43577E1FD5FD14622D24D97FCDCC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 77";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000800000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D83AF8EBE93E0B6B99CAFADE224937D1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 78";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000400000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("44042329128D56CAA8D084C8BD769D1E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 79";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000200000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("14102D72290DE4F2C430ADD1ED64BA1D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 80";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000100000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("449124097B1ECD0AE7065206DF06F03C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 81";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000080000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D060A99F8CC153A42E11E5F97BD7584A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 82";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000040000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("65605B3EA9261488D53E48602ADEA299");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 83";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000020000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C5E5CAD7A208DE8EA6BE049EFE5C7346");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 84";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000010000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4C280C46D2181646048DD5BC0C0831A5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 85";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000008000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5DD65CF37F2A0929559AABAFDA08E730");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 86";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000004000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("31F2335CAAF264172F69A693225E6D22");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 87";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000002000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3E28B35F99A72662590DA96426DD377F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 88";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000001000000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("570F40F5D7B20441486578ED344343BE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 89";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000800000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C54308AD1C9E3B19F8B7417873045A8C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 90";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000400000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CBF335E39CE13ADE2B696179E8FD0CE1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 91";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000200000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9C2FBF422355D8293083D51F4A3C18A9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 92";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000100000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5ED8B5A31ECEFAB16C9AA6986DA67BCE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 93";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000080000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("627815DCFC814ABC75900041B1DD7B59");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 94";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000040000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9EF3E82A50A59F166260494F7A7F2CC3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 95";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000020000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("878CD0D8D920888B5935D6C351128737");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 96";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000010000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E44429474D6FC3084EB2A6B8B46AF754");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 97";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000008000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EBAACF9641D54E1FB18D0A2BE4F19BE5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 98";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000004000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("13B3BF497CEE780E123C7E193DEA3A01");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 99";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000002000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6E8F381DE00A41161F0DF03B4155BFD4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 100";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000001000000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("35E4F29BBA2BAE01144910783C3FEF49");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 101";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000800000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("55B17BD66788CEAC366398A31F289FFB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 102";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000400000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("11341F56C0D6D1008D28741DAA7679CE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 103";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000200000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4DF7253DF421D83358BDBE924745D98C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 104";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000100000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BAE2EE651116D93EDC8E83B5F3347BE1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 105";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000080000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F9721ABD06709157183AF3965A659D9D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 106";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000040000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("19A1C252A613FE2860A4AE6D75CE6FA3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 107";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000020000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B5DDB2F5D9752C949FBDE3FFF5556C6E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 108";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000010000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("81B044FCFFC78ECCFCD171AAD0405C66");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 109";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000008000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C640566D3C06020EB2C42F1D62E56A9B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 110";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000004000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EA6C4BCF425291679FDFFD26A424FBCC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 111";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000002000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("57F6901465D9440D9F15EE2CBA5A4090");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 112";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000001000000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FBCFA74CADC7406260F63D96C8AAB6B1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 113";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000800000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DFF4F096CEA211D4BBDACA033D0EC7D1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 114";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000400000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1EE5190D551F0F42F675227A381296A9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 115";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000200000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F98E1905012E580F097623C10B93054F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 116";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000100000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7D43743D21DD3C9F168C86856558B9A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 117";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000080000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("632A9DDA730DAB67593C5D08D8AC1059");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 118";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000040000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E084317000715B9057BC9DE9F3AB6124");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 119";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000020000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("61F9EF33A0BB4E666C2ED99101919FAB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 120";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000010000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6DC1D68A11834657D46703C22578D59A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 121";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000008000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("53AC1548863D3D16F1D4DC7242E05F2C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 122";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000004000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E82CD587A408306AD78CEAE0916B9F8C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 123";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000002000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FD2D40EA6AD17A3A767F0A8600D6295");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 124";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000001000000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AD84CC8255ADB39DFCA23F92761AE7E9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 125";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000800000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F4F20CF7D51BEE7DA024A2B11A7ECA0B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 126";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000400000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5057691B85D9CE93A193214DB0A016B6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 127";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000200000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0F58C960876390BDEF4BB6BE95CAA1EE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 128";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000100000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9A3E66EEBC21BC0BD9430B341EF465FA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 129";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000080000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("20415035F34B8BCBCB28ABF07F78F0D4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 130";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000040000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AC89FC7BA10479EBF10DE65BCEF89B3C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 131";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000020000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("068FA75A30BE443171AF3F6FEB1A20D2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 132";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000010000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("50E02F213246C525A8C27700CA34B502");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 133";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000008000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("227DA47D5A0906DB3AB042BB0A695FB6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 134";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000004000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8663AC30ED12514F1DE46777F4514BFC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 135";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000002000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A987D4BC12E1DE9F4B6DF43567C34A8B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 136";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000001000000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6D5A0370F599ACA605F63B04E5143D0C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 137";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000800000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9809266E378B07B7AFDB3BAA97B7E442");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 138";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000400000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8F753252B30CCCACE12D9A301F4D5090");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 139";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000200000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("032465F6C0CE34D41962F561692A1AFF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 140";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000100000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C50E9AD5BEB8F3B00821DD47FF8AC093");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 141";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000080000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9C6FEA3D46268D54A6829B2AD25BB276");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 142";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000040000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0FD8575E87706F561343D7B3A41E044A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 143";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000020000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BEE9BEB3739540D88CBCE77925F0A114");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 144";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000010000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D24EAEE7FFFBAC3D6F26C2DCE0DCDE28");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 145";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000008000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("47771A90398FF0F7FA821C2F8F5E1398");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 146";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000004000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4639741B6F84B135AD118C8249B64ED0");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 147";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000002000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8EE5505EC85567697A3306F250A27720");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 148";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000001000000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7C8A19AC1AEFBC5E0119D91A5F05D4C2");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 149";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000800000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5141B9B672E54773B672E3A6C424887B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 150";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000400000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B5A2D3CD206653C6402F34FB0AE3613D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 151";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000200000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0F5BD9408738231D114B0A82753279A3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 152";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000100000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FEF033FF4268EA487FC74C5E43A45338");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 153";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000080000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A3EDC09DCD529B113910D904AD855581");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 154";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000040000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AB8FBB6F27A0AC7C55B59FDD36B72F1C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 155";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000020000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EEA44D5ED4D769CC930CD83D8999EC46");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 156";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000010000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6972276803AE9AA7C6F431AB10979C34");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 157";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000008000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("86DEAA9F39244101818178474D7DBDE9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 158";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000004000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("88C6B466EA361D662D8D08CBF181F4FE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 159";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000002000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("91AB2C6B7C63FF59F7CBEEBF91B20B95");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 160";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000001000000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2DFE6C146AD5B3D8C3C1718F13B48E01");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 161";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000800000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C7CFF1623451711391A302EEC3584AAA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 162";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000400000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("089FE845CC05011686C66019D18BE050");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 163";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000200000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("08C8410B9B427211A67124B0DCCEAD48");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 164";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000100000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8D91592F5566085254784606334D7629");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 165";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000080000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3298FEAAF2E1201D6299FF8846639C97");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 166";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000040000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C497CB9F0BDFE0EFC8C2F3F90760AA72");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 167";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000020000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2788AFD046E0309CBE4424690DA2AB89");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 168";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000010000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E9891707F25EF29FEE372890D4258982");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 169";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000008000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DB041D94A23D45D4D4DCED5A030CAF61");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 170";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000004000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("FFAFDBF0ECB18DF9EA02C27077448E6D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 171";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000002000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2DAAA42A7D0A1D3B0E4761D99CF2150A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 172";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000001000000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3B7A54CB7CF30ABE263DD6ED5BFE8D63");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 173";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000800000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EEFA090174C590C448A55D43648F534A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 174";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000400000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9E15798731ED42F43EA2740A691DA872");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 175";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000200000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("31FBD661540A5DEAAD1017CFD3909EC8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 176";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000100000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CDA9AE05F224140E28CB951721B44D6A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 177";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000080000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0C5BC512C60A1EAC3434EFB1A8FBB182");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 178";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000040000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("AA863610DEEEEB62D045E87EA30B59B5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 179";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000020000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6AC2448DE568D279C7EEBE1DF403920C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 180";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000010000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E2011E3D292B26888AE801215FD0CB40");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 181";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000008000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E06F3E15EE3A61672D1C99BADE5B9DBE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 182";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000004000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BB7027F0548CF6712CEB4C7A4B28E178");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 183";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000002000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("061EC21FB70FADBDF87C3BD2AE23825B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 184";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000001000000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("4C21F26FE94ABBAC381352375314C3EB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 185";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000800000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F7CEE6DD99909C2B569EEDA61ED8942E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 186";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000400000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("CE98C4A876C65E4CCB261EBB1D9DF7F5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 187";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000200000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A5491881CF833C3604ABC08044F402AC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 188";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000100000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A1BA16E64CCCB3087D57A768507B0BFC");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 189";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000080000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D55951E202D2949EBD3BE43120C738BF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 190";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000040000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EBB8E43069E69F450EFEC65DCD52B7FD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 191";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000020000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2B292135663B4AA5ABFE9423D57E7EE9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 192";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000010000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E91BF974B3BE3AD966249D8655292A85");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 193";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000008000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("384365998EAA9562236CC58F6ADF9610");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 194";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000004000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("C2E997012AA3D4D8D359C9A947CBE69F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 195";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000002000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F49421204148BA213BE87E2D5C22B0BF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 196";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000001000000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("82ED0ED9953AA92E4DF30929CA65C00F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 197";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000800000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("291EB1D11653C8479437C74A977F5106");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 198";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000400000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("BCB997B1939B8983ABD550D6025683E3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 199";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000200000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("1FBA2592C6F489775CAADA71F9B983E9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 200";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000100000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("969F66F217AF1A3DB9E41C1B29039824");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 201";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000080000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A54BB7D6B17E423AC0A7744C19073CB8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 202";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000040000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B0AC6E6578D1021F47DCF9748A32EAD5");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 203";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000020000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B87B361C3B7B194C77A4358D4669153E");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 204";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000010000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("46A133847F96EAA8282A799DC8899D58");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 205";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000008000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2265EC3A9F2D5C9547A091CC8CFB18EA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 206";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000004000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("54CBF3A6FC4FE56D426117AA1FFD1DDE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 207";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000002000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5312877CCEAB6CFB0905394A370A8003");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 208";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000001000000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7190BD6EC613FE38B84ECFE28F702FE4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 209";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000800000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D1FA5B9CA89A43B04C05F0EF29EF68CD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 210";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000400000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("808285751548ED934FD1056D2D9AE8BA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 211";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000200000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2758DEF3E7B95A9AE89777BE64D5A6CF");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 212";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000100000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("07D81F87DB3E0ACC82B01E08FB22F3C1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 213";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000080000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8DA250E5553D650711A75EE1CB4FD1C7");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 214";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000040000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("A93D946BD0E87F32719DF5F158CEE669");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 215";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000020000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("03945236EC2A4D4EAF30B8ABEB54330D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 216";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000010000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("11CC35301F24B79DDE31AEA2D1354F88");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 217";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000008000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E73715B3E8D9A290F44AE6FFBF247E5D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 218";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000004000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("7345E07732B71CB158BBF64CCA5C5B96");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 219";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000002000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6E128F296D24705A1924FD9B70C4ED04");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 220";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000001000000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("95A789776F036783FBD330947083F54F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 221";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000800000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("360DEC2533EA4AA2E3E54FD3DE2906EB");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 222";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000400000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E68EFD7FECF4D601EA22727BD764965B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 223";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000200000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9065C64A8BFF44AC33EDBB611CF83D7B");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 224";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000100000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8F33C8DF2A7A51CE8090E8F123BC3723");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 225";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000080000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("807F391FFBA8291BA625623210F99018");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 226";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000040000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5E8B3F3A701522CE5CAA761C929D6292");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 227";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000020000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("3BA404DC38735A78289E3809E8364835");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 228";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000010000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D23BEDBAD229F8305DC425B6B759DCC9");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 229";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000008000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("44880F21CF5913040AE376AEE2A10AD8");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 230";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000004000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("9BC98E29D057C0E828C3B5CCE69256C1");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 231";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000002000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B293CC7A975DA141A68279368057CC41");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 232";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000001000000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("8D60FB87ACD91385B313BE5F1D7BD30F");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 233";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000800000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2C8E56132D70291B303C48FDF75543CD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 234";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000400000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D1F80035B826791F6CE4E59B7DB1BB0D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 235";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000200000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("42CE6224FC36469339A133DD08173BD4");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 236";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000100000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("61817155EA41BCBA2AF7F06AE7CBF585");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 237";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000080000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D1923A9866068D2EF5FB77D57C3315B6");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 238";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000040000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("B37CBDB5D719F49691CA968EF2E84140");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 239";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000020000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EC974E653A055D7F8F22171030F68E1D");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 240";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000010000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("DDE5D3B9AAD9C32213BB3675A822499C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 241";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000008000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D3B6E9216EA1AE57EB1C628A3C38AB78");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 242";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000004000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("82C99ECC69472B7E96324B042AE8B87A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 243";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000002000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("97144DC5338C43600F84439C0AA0D147");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 244";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000001000");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("400AC4A0BBADA1DB2121EB144C7E5209");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 245";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000800");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("EFD9D550EB419ED278F4885A490AB54C");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 246";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000400");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("2AB7816E149B7C0404C88A8857793670");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 247";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000200");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("5B591DFF9E8DEE15BAD24C025DBCA481");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 248";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000100");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("0C06633E30721C3749F49AD8CBF2B754");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 249";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000080");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("96D6D31A41B5123B2035FD91A921D4CA");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 250";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000040");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E7F6C34D86668BC2805CA7793C5E86AD");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 251";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000020");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("F46DFF5FF500D6879C4D3E45CF0CF0F3");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 252";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000010");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("60D842D9C61DA7495C116197B7CECBBE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 253";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000008");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("D45B24EDB673353EBDF248B8FA06B67A");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 254";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000004");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("119EAEBCC165D0BD02C0D35DC82EF992");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 255";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000002");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("E673143680414ADA301D0ED34626B9FE");
		test_list.push_back(tmp);

		tmp.test_name = "Variable Key Known Answer Test 256";
		tmp.key = tc::cli::FormatUtil::hexStringToBytes("0000000000000000000000000000000000000000000000000000000000000001");
		tmp.ciphertext = tc::cli::FormatUtil::hexStringToBytes("6B6CFE160A6263631B292F879EEFF926");
		test_list.push_back(tmp);
	}
}