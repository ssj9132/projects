import DateTimeDay from './DateTimeDay';
import PrivacyStatement from './PrivacyStatement';

const Footer = () => {
  const footerStyle = {
    backgroundColor: '#002855',
    color: 'white',
    padding: '10px 20px',
    display: 'flex',
    justifyContent: 'space-between',
    alignItems: 'center',
    position: 'fixed',
    bottom: 0,
    left: 0,
    width: '100%',
    fontFamily: 'Arial, sans-serif',
    zIndex: 1000,
  };

  return (
    <div style={footerStyle}>
      <DateTimeDay />
      <PrivacyStatement />
    </div>
  );
};

export default Footer;
