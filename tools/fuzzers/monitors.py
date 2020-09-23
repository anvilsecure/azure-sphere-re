import requests
from boofuzz import BaseMonitor


class GatewayMonitor(BaseMonitor):

    def __init__(self, target, timeout=0.5):
        self.target = target
        self.timeout = timeout
    
    def alive(self):
        try:
            r = requests.get(f"https://{self.target}/status", verify=False, timeout=self.timeout)
            return True
        except:
            return False
    
    def post_send(self, target=None, fuzz_data_logger=None, session=None):
        try:
            r = requests.get(f"https://{self.target}/status", verify=False, timeout=self.timeout)
            fuzz_data_logger.log_info("alive!: " + r.text)
            return True
        except requests.exceptions.ConnectTimeout:
            fuzz_data_logger.log_info("alive connection timeout...")
        except ConnectionRefusedError:
            fuzz_data_logger.log_info("alive connection refused...")
        except:
            fuzz_data_logger.log_info("failed to get status!")
        return False
