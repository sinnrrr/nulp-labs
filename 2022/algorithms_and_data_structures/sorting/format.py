from colorama import Fore, Style


class Format:

    @staticmethod
    def header(text: str) -> str:
        return Fore.RED + text + Style.RESET_ALL

    @staticmethod
    def algo_options(options) -> str:
        formatted_options = []

        for idx, option in enumerate(options):
            formatted_options.append(Fore.BLUE + str(idx + 1) + ") " +
                                     Fore.CYAN + option[0] + Style.RESET_ALL)

        return '\n'.join(formatted_options)

    @staticmethod
    def input(text, default_value):
        default_value_text = f" [{Fore.GREEN}{default_value}{Fore.BLUE}]" if default_value is not None else ""

        return Fore.BLUE + f"{text}{default_value_text}: " + Style.RESET_ALL
