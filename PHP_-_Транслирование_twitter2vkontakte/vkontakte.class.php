<?
class VkontakteAPI {
	var $email = '';
	var $password = '';
	var $pageBody;
	var $userID = '';
	var $activityhash = '';

	function __construct($email, $password)
	{
		$this->email = $email;
		$this->password = $password;
	}	

	function auth()
	{
		$ch = curl_init();
		curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1); 
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
		curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; (R1 1.5))");
		curl_setopt($ch, CURLOPT_COOKIEFILE, 'cookies.txt');
		curl_setopt($ch, CURLOPT_COOKIEJAR,  'cookies.txt');
		curl_setopt($ch, CURLOPT_TIMEOUT, 30);

		curl_setopt ($ch, CURLOPT_URL, 'http://vkontakte.ru/'); 

		$body = curl_exec($ch);
		sleep(2);

		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, "email=".$this->email."&pass=".$this->password);
		curl_setopt ($ch, CURLOPT_URL, 'http://vkontakte.ru/login.php'); 
		$body = curl_exec($ch);
	
		$this->pageBody = curl_exec($ch);
		sleep(2);

		$arr = array();
		preg_match_all("|<input\stype=\"hidden\"\sid=\"mid\"\svalue=\"(.+)\">|U", $this->pageBody, $arr);
		$this->userID = $arr[1][0];

		preg_match_all("|<input\stype=\'hidden\'\sid=\'activityhash\'\svalue=\'(.+)\'>|U", $this->pageBody, $arr);
		$this->activityhash = $arr[1][0];
	
		curl_close($ch);
	}

	function getStatus()
	{
		$arr = array();
		preg_match_all("|activity_editor\.show\(\)\;return\sfalse\;\">(.+)<|U", $this->pageBody, $arr);
		$status = $arr[1][0];	
		return substr($status, 0, strlen($status) - 1);
	}

	function setStatus($text)
	{
		$ch = curl_init();
		curl_setopt ($ch, CURLOPT_RETURNTRANSFER, 1); 
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
		curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; (R1 1.5))");
		curl_setopt($ch, CURLOPT_COOKIEFILE, 'cookies.txt');
		curl_setopt($ch, CURLOPT_COOKIEJAR,  'cookies.txt');
		curl_setopt($ch, CURLOPT_TIMEOUT, 30);

		curl_setopt($ch, CURLOPT_URL, 'http://vkontakte.ru/profile.php'); 
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, "setactivity=".urlencode($text)."&activityhash=".$this->activityhash);

	        curl_setopt($ch, CURLOPT_REFERER, 'http://vkontakte.ru/id'.$this->userID);

		$body = curl_exec($ch);

		curl_close($ch);	
	}
}
?>