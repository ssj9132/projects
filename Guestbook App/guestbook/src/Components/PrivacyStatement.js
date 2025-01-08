const PrivacyStatement = () => {
    const privacyLinkStyle = {
      color: 'white',
      textDecoration: 'none',
    };
  
    return (
      <a
        href="https://policies.google.com/privacy?hl=en-US"
        style={privacyLinkStyle}
        target="_blank"
        rel="noopener noreferrer"
      >
        Privacy Statement
      </a>
    );
  };
  
  export default PrivacyStatement;
  