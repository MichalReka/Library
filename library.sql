-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Czas generowania: 02 Lut 2020, 20:37
-- Wersja serwera: 10.3.15-MariaDB
-- Wersja PHP: 7.3.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Baza danych: `biblioteka`
--

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `books`
--

CREATE TABLE `books` (
  `ID` int(11) NOT NULL,
  `Tytul` char(100) COLLATE utf8_polish_ci NOT NULL,
  `Autor` char(100) COLLATE utf8_polish_ci NOT NULL,
  `Status` int(11) NOT NULL DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `books`
--

INSERT INTO `books` (`ID`, `Tytul`, `Autor`, `Status`) VALUES
(1, 'Równoumagicznienie', 'Terry Pratchett', 1),
(2, 'Dziady czesc III', 'Adam Mickiewicz', 1),
(3, 'Starcie krolow', 'George R. R. Martin', 1),
(4, 'Ferdydurke', 'Witold Gombrowicz', 1);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `borrowings`
--

CREATE TABLE `borrowings` (
  `ID` int(11) NOT NULL,
  `BookID` int(11) NOT NULL,
  `ReaderID` int(11) NOT NULL,
  `Date` date NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `jobs`
--

CREATE TABLE `jobs` (
  `ID` int(11) NOT NULL,
  `Name` text COLLATE utf8_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `jobs`
--

INSERT INTO `jobs` (`ID`, `Name`) VALUES
(1, 'Admin'),
(2, 'Pracownik informacji'),
(3, 'Bibliotekarz');

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `readers`
--

CREATE TABLE `readers` (
  `ID` int(11) NOT NULL,
  `Name` text COLLATE utf8_polish_ci NOT NULL,
  `Address` text COLLATE utf8_polish_ci NOT NULL,
  `Postal Code` text COLLATE utf8_polish_ci NOT NULL,
  `PhoneNumber` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `readers`
--

INSERT INTO `readers` (`ID`, `Name`, `Address`, `Postal Code`, `PhoneNumber`) VALUES
(1, 'Michal', 'Gorzow Wielkopolski', '66-400', 692638994);

-- --------------------------------------------------------

--
-- Struktura tabeli dla tabeli `workers`
--

CREATE TABLE `workers` (
  `ID` int(11) NOT NULL,
  `FirstName` text COLLATE utf8_polish_ci NOT NULL,
  `LastName` text COLLATE utf8_polish_ci NOT NULL,
  `City` text COLLATE utf8_polish_ci NOT NULL,
  `Address` text COLLATE utf8_polish_ci NOT NULL,
  `Postal Code` text COLLATE utf8_polish_ci NOT NULL,
  `Bank account` int(11) NOT NULL,
  `JobID` int(11) NOT NULL,
  `Password` int(11) NOT NULL DEFAULT 1234
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Zrzut danych tabeli `workers`
--

INSERT INTO `workers` (`ID`, `FirstName`, `LastName`, `City`, `Address`, `Postal Code`, `Bank account`, `JobID`, `Password`) VALUES
(1, 'Michal', 'Reka', 'Gorzow Wielkopolski', 'Moniuszki 45', '66-400', 0, 1, 1234),
(9, 'Zuzanna', 'Ku$zyk', 'Horeszkowo', '5e', '451-345', 1234, 1, 1234),
(10, 'Jan', 'Psiuk', 'Gorzow', 'Matejki 12', '66-400', 2312, 3, 1234),
(11, 'Zuzia', 'Kuszyk', 'Chwarszczany', '4e', '12312-213', 231193, 2, 1234);

--
-- Indeksy dla zrzutów tabel
--

--
-- Indeksy dla tabeli `books`
--
ALTER TABLE `books`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `borrowings`
--
ALTER TABLE `borrowings`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `BookID` (`BookID`),
  ADD KEY `ReaderID` (`ReaderID`);

--
-- Indeksy dla tabeli `jobs`
--
ALTER TABLE `jobs`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `readers`
--
ALTER TABLE `readers`
  ADD PRIMARY KEY (`ID`);

--
-- Indeksy dla tabeli `workers`
--
ALTER TABLE `workers`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `JobID` (`JobID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT dla tabeli `books`
--
ALTER TABLE `books`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT dla tabeli `borrowings`
--
ALTER TABLE `borrowings`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT dla tabeli `readers`
--
ALTER TABLE `readers`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT dla tabeli `workers`
--
ALTER TABLE `workers`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- Ograniczenia dla zrzutów tabel
--

--
-- Ograniczenia dla tabeli `borrowings`
--
ALTER TABLE `borrowings`
  ADD CONSTRAINT `borrowings_ibfk_1` FOREIGN KEY (`BookID`) REFERENCES `books` (`ID`),
  ADD CONSTRAINT `borrowings_ibfk_2` FOREIGN KEY (`ReaderID`) REFERENCES `readers` (`ID`);

--
-- Ograniczenia dla tabeli `workers`
--
ALTER TABLE `workers`
  ADD CONSTRAINT `workers_ibfk_1` FOREIGN KEY (`JobID`) REFERENCES `jobs` (`ID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
