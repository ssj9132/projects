const Footer = () => {
  const footerStyle = {
    backgroundColor: '#124110',
    color: '#FAF5E9',
    padding: '10px 20px',
    display: 'flex',
    justifyContent: 'space-between',
    alignItems: 'center',
    width: '100%',
    fontFamily: 'Arial, sans-serif',
    zIndex: 1000,
  };

  const textStyle = {
    margin: '10px 0',
  };

  return (
    <div style={footerStyle}>
      <p style={textStyle}>© 2024 Shaun Jacob</p>
      <p style={textStyle}>All Rights Reserved</p>
    </div>
  );
};

export default Footer;
