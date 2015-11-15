def isPalindrome(s):
    return s == s[::-1]

canal = 'a man a plan a canal panama'
new_canal = canal.replace(' ', '')
print canal
print new_canal
print isPalindrome(new_canal)