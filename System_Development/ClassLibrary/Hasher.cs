using System.Text;

public static class Hasher
{
    public static string ByteArrayToHexString(byte[] ba)
    {
        StringBuilder hex = new StringBuilder(ba.Length);
        foreach (var b in ba)
        {
            hex.AppendFormat("{0:x2}", b);
        }
        return hex.ToString();
    }

    public static string GenerateHash(string input)
    {
        byte[] bytes = Encoding.UTF8.GetBytes(input);
        System.Security.Cryptography.SHA256Managed hashString =
            new System.Security.Cryptography.SHA256Managed();
        byte[] hash = hashString.ComputeHash(bytes);
        return ByteArrayToHexString(hash);
    }
}