-- MySQL dump 10.13  Distrib 5.6.30, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: ARPLogs
-- ------------------------------------------------------
-- Server version	5.6.30-0ubuntu0.15.10.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Logs`
--

DROP TABLE IF EXISTS `Logs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Logs` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ip` varchar(255) DEFAULT NULL,
  `mac` varchar(255) DEFAULT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Logs`
--

LOCK TABLES `Logs` WRITE;
/*!40000 ALTER TABLE `Logs` DISABLE KEYS */;
INSERT INTO `Logs` VALUES (1,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:11'),(2,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:50'),(3,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:50'),(4,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:51'),(5,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:51'),(6,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:51'),(7,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:51'),(8,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:51'),(9,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:51'),(10,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:52'),(11,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:52'),(12,'d¢ÿÿÿ','ØËŠÕ~¼d¢ÿÿÿ','2016-09-26 14:49:54');
/*!40000 ALTER TABLE `Logs` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-09-26  9:57:34
