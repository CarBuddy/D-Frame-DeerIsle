class Encoding 
{
	static const ref TStringArray HEX_BYTES = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"
	};
	
	static const ref TStringArray BASE64_TABLE = {
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
		"Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f",
		"g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
		"w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "+", "/",
	};
	
    static array<int> GetBytes(string str)
    {
        array<int> result = {};
        for (int i = 0; i < str.Length(); i++) {
            result.Insert(Encoding.GetByte(str[i]));
        }
		
        return result;
    }
	
    static int GetByte(string character)
    {
        return UInt8.Convert(character[0].Hash());
    }
	
	/*static string ToHex(string ascii)
	{
		return Encoding.ToHex(ascii.Hash());
	}*/
	
    static string ToHex(int ascii)
    {
		string result;
		
		// There might be some Math.Log2 optimization to make the code shorter
		// but im almost certain that this is the fastest way to do this		
		while (true) {
			result = HEX_BYTES[ascii % 16] + result;
			ascii >>= 4;
			if (ascii <= 0) {
				return result;
			}
		}
		
        return result;
    }
	
	static int FromHex(string hex)
	{
		int result;
		
		// Formatting
		hex.ToUpper();
		hex.TrimInPlace();
		
		for (int i = 0; i < hex.Length(); i++) {
			/* The additional math at the end is to invert the direction of the for loop
			 but only for the pow, since the index operator works from the first item,
			 we want ^0 on the last digit, and ^n-1 on the first digit */
			result += HEX_BYTES.Find(hex[i]) * Math.Pow(16, Math.AbsInt(i - hex.Length() + 1));
		}

		return result;
	}
		
    static string FromBytesHex(notnull array<int> data)
    {
        string hex;
        for (int i = 0; i < data.Count(); i++) {
            hex += Encoding.ToHex(data[i]);
        }
		
        return hex;
    }
	
	// todo base64 encoding so we can convert Steamid64 to DayZ ID
	static string ToBase64(string input)
	{
		string result;
		input.TrimInPlace();
		
		array<int> byte_array = {};
		for (int i = 0; i < input.Length(); i++) {
			byte_array.InsertAt(input[i].Hash(), i);
		}
		
		
		
		return result;
	}
}