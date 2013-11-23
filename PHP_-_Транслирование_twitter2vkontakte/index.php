<?
include 'twitter.class.php';
include 'vkontakte.class.php';
include 'config.php';

$twitter = new twitter();

$twitter->username = $twitterUser;
$twitter->password = $twitterPassword;

$statusTwitter = $twitter->userTimeline()->status->text;

$vk = new VkontakteAPI($vkontakteEmail, $vkontaktePassword);
$vk->auth();

$statusVkontakte = $vk->getStatus();                       

if ($statusTwitter != $statusVkontakte)
{
	$vk->setStatus($statusTwitter);
}
?>
